#version 450 core

layout(location = 0) in vec2 aVertexCoord;

out vec2 TexCoord;
out vec4 FragCoord;
out vec3 NormalVec;

uniform mat4 u_VPTrans;
uniform mat4 u_VTrans;

void main()
{
	TexCoord = aVertexCoord;
	FragCoord = u_VTrans * vec4(aVertexCoord.x, 0.0f, aVertexCoord.y, 1.0f);
	NormalVec = vec3(u_VTrans * vec4(0.0f, 1.0f, 0.0f, 0.0f));
	gl_Position = u_VPTrans * vec4(aVertexCoord.x, 0.0f, aVertexCoord.y, 1.0f);
}