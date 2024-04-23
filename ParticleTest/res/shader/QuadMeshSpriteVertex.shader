#version 450 core

layout(location = 0) in vec2 aVertexCoord;

out vec2 TexCoord;

uniform mat4 u_MVPTrans;

void main()
{
	TexCoord = aVertexCoord;
	gl_Position = u_MVPTrans * vec4(aVertexCoord.x, 0.0f, aVertexCoord.y, 1.0f);
}