#version 450 core

// 输入变量
in vec3 NormalVec;
in vec3 HalfVec;
in vec3 FragPos;		// 相机坐标系的顶点坐标
in vec2 TexCoord;

uniform vec4 u_Color;

// 材质系统
struct Material
{
	sampler2D DiffuseTex;
	vec2 DiffuseTexOffset;
	vec2 DiffuseTexScale;
	
	sampler2D SpecularTex;
	vec2 SpecularTexOffset;
	vec2 SpecularTexScale;
	
	sampler2D NormalTex;
	vec2 NormalTexOffset;
	vec2 NormalTexScale;
	
	sampler2D ParallaxTex;
	vec2 ParallaxTexOffset;
	vec2 ParallaxTexScale;
	
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
layout(std140)buffer DirLights
{
	int countDirLight;
	struct dataDirLights[];
};

layout(std140)buffer PointLights
{
	int countDirLight;
	struct dataPointLights[];
};

layout(std140)buffer SpotLights
{
	int countDirLight;
	struct dataSpotLights[];
};


// 输出
out vec4 FragColor;

vec4 FragmentShader()
{
	vec2 texCoord = TexCoord / u_Material.DiffuseTexScale + u_Material.DiffuseTexOffset;
	return texture2D(u_Material.DiffuseTex, texCoord) * u_Color;
}


void main()
{
	FragColor = FragmentShader();
}