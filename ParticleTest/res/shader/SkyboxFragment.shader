#version 450 core

in vec3 SampleVec;
out vec4 FragColor;

uniform samplerCube u_CubeMap;

void main()
{
	FragColor = texture(u_CubeMap, SampleVec);
}