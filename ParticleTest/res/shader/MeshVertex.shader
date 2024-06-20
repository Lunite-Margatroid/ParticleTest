#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_MVPTrans;
uniform mat3 u_NormalTrans;
uniform mat4 u_MVTrans;
uniform mat4 u_VTrans;


out vec2 TexCoord;


void main()
{
	gl_Position = u_MVPTrans * vec4(aPosition, 1.0f);
	
	TexCoord = aTexCoord;
}