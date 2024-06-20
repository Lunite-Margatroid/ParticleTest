#version 450 core

in vec3 Ambient;
in vec3 Diffuse;
in vec3 Specular;
in vec2 TexCoord;

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
uniform vec4 u_Color;


vec4 FragmentShader()
{
	// 纹理颜色
	vec2 texCoord = TexCoord / u_Material.DiffuseTexScale + u_Material.DiffuseTexOffset;
	vec2 specularTexCoord = TexCoord / u_Material.SpecularTexScale + u_Material.SpecularTexOffset;
	
	vec4 diffuseTexColor = texture2D(u_Material.DiffuseTex, texCoord);
	diffuseTexColor = diffuseTexColor * u_Material.DiffuseTexWeight;
	
	vec4 specularTexColor = texture2D(u_Material.SpecularTex, specularTexCoord);
	specularTexColor = specularTexColor * u_Material.SpecularTexWeight;
	
	return (
			diffuseTexColor * vec4((Ambient + Diffuse),1.0f)
			+ specularTexColor * vec4(Specular, 1.0f)
			)
			* u_Color;

}

void main()
{
	FragColor = FragmentShader();
}