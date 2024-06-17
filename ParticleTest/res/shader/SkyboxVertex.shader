#version 450 core
layout(location = 0)in vec3 aPos;

out vec3 SampleVec;
uniform mat4 u_ViewTrans;
uniform mat4 u_ProjectionTrans;

void main()
{
	SampleVec = aPos;
	
	gl_Position = u_ProjectionTrans * vec4(mat3(u_ViewTrans) * aPos, 1.0f);
}