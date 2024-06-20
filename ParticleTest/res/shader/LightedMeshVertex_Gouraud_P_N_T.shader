#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_MVPTrans;
uniform mat4 u_MTrans;
uniform vec3 u_CameraPos;
uniform mat3 u_NormalTrans;

out vec3 Ambient;
out vec3 Diffuse;
out vec3 Specular;
out vec2 TexCoord;

vec3 VertexPos;	// 顶点的世界坐标
vec3 NormalVec;	// 世界坐标系 法向量
vec3 ViewVec;

// 材质系统
struct Material
{
	sampler2D DiffuseTex;
	vec2 DiffuseTexOffset;
	vec2 DiffuseTexScale;
	float DiffuseTexWeight;
	
	sampler2D SpecularTex;
	vec2 SpecularTexOffset;
	vec2 SpecularTexScale;
	float SpecularTexWeight;
	
	sampler2D NormalTex;
	vec2 NormalTexOffset;
	vec2 NormalTexScale;
	float NormalTexWeight;
	
	sampler2D ParallaxTex;
	vec2 ParallaxTexOffset;
	vec2 ParallaxTexScale;
	float ParallaxTexWeight;
	
	float shininess;
};

uniform Material u_Material;


/*-------------- 光照 ------------------*/

// 平行光
struct DirLight
{
	vec3 ambient;			// 环境光
    vec3 diffuse;			// 漫反射
    vec3 specular;			// 镜面反射

    vec3 direction;			// 光照方向
};
// 点光源
struct PointLight
	{
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

		vec3 position;
			// 衰减
		float kConstant;		// 常数项
		float kLinear;			// 一次项
		float kQuadratic;		// 2次项
	};
// 聚光灯
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
				
	vec3 position;
	vec3 direction;
				
				// 衰减
	float kConstant;		// 常数项
	float kLinear;			// 一次项
	float kQuadratic;		// 2次项

	float innerbdr;			// 内边界的cos
	float outerbdr;			// 外边界的cos
				// innerbdr > outerbdr
			};
layout(std140, binding = 1)buffer DirLights
{
	int countDirLight;
	DirLight dataDirLights[];
};

layout(std140,binding = 2)buffer PointLights
{
	int countPointLight;
	PointLight dataPointLights[];
};

layout(std140, binding = 3)buffer SpotLights
{
	int countSpotLight;
	SpotLight dataSpotLights[];
};

void CulcDirLight(out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	ambient = vec3(0.0f);
	diffuse = vec3(0.0f);
	specular = vec3(0.0f);
	
	for(int i =0; i < countDirLight;i++)
	{
	DirLight light = dataDirLights[i];
	vec3 dir = -normalize(light.direction);
	// ambient
		ambient = ambient + light.ambient;
	// diffuse
		diffuse = diffuse + max(dot(NormalVec , dir), 0.0f) * light.diffuse;
	// specular
		// blinn phong
		// specular = specular + pow(max(dot(HalfVec_ , dir), 0.0f), u_Material.shininess) * light.specular;
		// phong
		specular = specular + pow(max(dot(-reflect(dir, NormalVec), ViewVec), 0.0f),u_Material.shininess) * light.specular;
	}
}

void CulcPointLight(out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	ambient = vec3(0.0f);
	diffuse = vec3(0.0f);
	specular = vec3(0.0f);
	
	for(int i =0;i<countPointLight;i++)
	{
		PointLight light = dataPointLights[i];
		vec3 dir = light.position - VertexPos;
		float dist = length(dir);
		dir = dir / dist;
		// 衰减系数
		float k = light.kConstant + (light.kLinear + light.kQuadratic * dist) * dist;
		// ambient
		ambient = ambient + light.ambient / k;
		// diffuse
		diffuse = diffuse + max(dot(dir, NormalVec), 0.0f) / k * light.diffuse;
		// specular
		//specular = specular + pow(max(dot(HalfVec_, dir), 0.0f), u_Material.shininess) / k * light.specular;
		// phong
		specular = specular + pow(max(dot(-reflect(dir, NormalVec), ViewVec), 0.0f),u_Material.shininess) / k * light.specular;
	}
}

void CulcSpotLight(out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	ambient = vec3(0.0f);
	diffuse = vec3(0.0f);
	specular = vec3(0.0f);
	
	for(int i =0;i<countSpotLight;i++)
	{
		SpotLight light = dataSpotLights[i];
		vec3 dir = light.position - VertexPos;
		float dist = length(dir);
		dir = dir / dist;
		
		// 照射系数  判断是否在照射范围内
		float kLight = dot(-dir , normalize(light.direction));
		kLight = clamp((kLight - light.outerbdr) / (light.innerbdr - light.outerbdr), 0.0f, 1.0f );
		// 衰减系数
		float k = light.kConstant + (light.kLinear + light.kQuadratic * dist) * dist;
		
		kLight = kLight / k;
		// ambient
		ambient = ambient + light.ambient / k;
		// diffuse
		diffuse = diffuse + max(dot(dir, NormalVec), 0.0f) * kLight * light.diffuse;
		// specular
		// specular = specular + pow(max(dot(HalfVec_, dir), 0.0f), u_Material.shininess) * kLight * light.specular;	
		specular = specular + pow(max(dot(-reflect(dir, NormalVec), ViewVec), 0.0f),u_Material.shininess) * kLight * light.specular;
	}
}


void main()
{
	VertexPos = vec3(u_MTrans * vec4(aPos,1.0f));
	gl_Position = u_MVPTrans * vec4(aPos, 1.0f);
	
	NormalVec = normalize(u_NormalTrans * aNormal);
	ViewVec = normalize(u_CameraPos - VertexPos);
	
	
	// 计算光照
	vec3 dirAmbient;
	vec3 dirDiffuse;
	vec3 dirSpecular;
	CulcDirLight(dirAmbient, dirDiffuse, dirSpecular);
	
	vec3 pointAmbient;
	vec3 pointDiffuse;
	vec3 pointSpecular;
	CulcPointLight(pointAmbient, pointDiffuse, pointSpecular);
	
	vec3 spotAmbient;
	vec3 spotDiffuse;
	vec3 spotSpecular;
	CulcSpotLight(spotAmbient, spotDiffuse, spotSpecular);
	
	Ambient = dirAmbient + pointAmbient + spotAmbient;
	Diffuse = dirDiffuse + pointDiffuse + spotDiffuse;
	Specular = dirSpecular + pointSpecular + spotSpecular;
	
	TexCoord = aTexCoord;
}