#version 450 core

// 输入变量
in vec3 NormalVec;	vec3 NormalVec_;
in vec3 FragPos;// 世界坐标系的顶点坐标	
					vec3 ViewVec_;	
in vec2 TexCoord;

in vec3 CameraPos;

uniform vec4 u_Color;
uniform vec3 u_CameraPos;
// 输出
out vec4 FragColor;

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
		diffuse = diffuse + max(dot(NormalVec_ , dir), 0.0f) * light.diffuse;
	// specular
		// blinn phong
		// specular = specular + pow(max(dot(HalfVec_ , dir), 0.0f), u_Material.shininess) * light.specular;
		// phong
		specular = specular + pow(max(dot(-reflect(dir, NormalVec_), ViewVec_), 0.0f),u_Material.shininess) * light.specular;
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
		vec3 dir = light.position - FragPos;
		float dist = length(dir);
		dir = dir / dist;
		// 衰减系数
		float k = light.kConstant + (light.kLinear + light.kQuadratic * dist) * dist;
		// ambient
		ambient = ambient + light.ambient / k;
		// diffuse
		diffuse = diffuse + max(dot(dir, NormalVec_), 0.0f) / k * light.diffuse;
		// specular
		//specular = specular + pow(max(dot(HalfVec_, dir), 0.0f), u_Material.shininess) / k * light.specular;
		// phong
		specular = specular + pow(max(dot(-reflect(dir, NormalVec_), ViewVec_), 0.0f),u_Material.shininess) / k * light.specular;
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
		vec3 dir = light.position - FragPos;
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
		diffuse = diffuse + max(dot(dir, NormalVec_), 0.0f) * kLight * light.diffuse;
		// specular
		// specular = specular + pow(max(dot(HalfVec_, dir), 0.0f), u_Material.shininess) * kLight * light.specular;	
		specular = specular + pow(max(dot(-reflect(dir, NormalVec_), ViewVec_), 0.0f),u_Material.shininess) * kLight * light.specular;
	}
}

vec4 FragmentShader()
{
	// 先把输入单位化
	NormalVec_ = normalize(NormalVec);
	ViewVec_ = normalize(CameraPos-FragPos);
	// 纹理颜色
	vec2 texCoord = TexCoord / u_Material.DiffuseTexScale + u_Material.DiffuseTexOffset;
	vec2 specularTexCoord = TexCoord / u_Material.SpecularTexScale + u_Material.SpecularTexOffset;
	
	vec4 diffuseTexColor = texture2D(u_Material.DiffuseTex, texCoord);
	diffuseTexColor = diffuseTexColor * u_Material.DiffuseTexWeight;
	
	vec4 specularTexColor = texture2D(u_Material.SpecularTex, specularTexCoord);
	specularTexColor = specularTexColor * u_Material.SpecularTexWeight;
	
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
	
	vec3 ambient = dirAmbient + pointAmbient + spotAmbient;
	vec3 diffuse = dirDiffuse + pointDiffuse + spotDiffuse;
	vec3 specular = dirSpecular + pointSpecular + spotSpecular;
	
	
	
	return (
			diffuseTexColor * vec4((ambient + diffuse),1.0f)
			+ specularTexColor * vec4(specular, 1.0f)
			)
			* u_Color;
}



void main()
{
	FragColor = FragmentShader();
}