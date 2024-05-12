#version 450 core

in vec3 NormalVec;
in vec3 HalfVec;
in vec3 FragPos;		// 相机坐标系的顶点坐标
in vec2 TexCoord;

uniform sampler2D u_Tex;
uniform vec4 u_Color;

out vec4 FragColor;

void main()
{
	FragColor = texture2D(u_Tex, TexCoord) * u_Color;
}