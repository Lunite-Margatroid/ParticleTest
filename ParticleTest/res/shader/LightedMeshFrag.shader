#version 450 core

in vec3 NormalVec;
in vec3 HalfVec;
in vec3 FragPos;		// 相机坐标系的顶点坐标
in vec2 TexCoord;

uniform sampler2D u_Tex;
uniform vec2 u_TexOffset;
uniform vec2 u_TexScale;

layout(std140)buffer DirLights
{
	int countDirLight;
	ParticleVertex particles[];
};

layout(std140)buffer PointLights
{
	int countDirLight;
	ParticleVertex particles[];
};

layout(std140)buffer SpotLights
{
	int countDirLight;
	ParticleVertex particles[];
};



uniform vec4 u_Color;

out vec4 FragColor;

vec4 FragmentShader()
{
	vec2 texCoord = TexCoord / u_TexScale + u_TexOffset;
	return texture2D(u_Tex, texCoord) * u_Color;
}


void main()
{
	FragColor = FragmentShader();
}