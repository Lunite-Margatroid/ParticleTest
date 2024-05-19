#version 450 core

in vec3 NormalVec;
in vec3 HalfVec;
in vec3 FragPos;		// 相机坐标系的顶点坐标
in vec2 TexCoord;

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

uniform vec4 u_Color;

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