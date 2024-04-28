#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aVel;
layout(location = 2) in float aT;

uniform mat4 u_MVPTrans;
uniform float u_DeltaTime;

uniform float u_VertexSize;
uniform vec3 u_Accelerate;

out float out_T;
out vec3 out_Pos;
out vec3 out_Vel;

void main()
{
	vec4 pos = u_MVPTrans * vec4(aPos, 1.0f);
	out_Pos = aPos + aVel;
	out_Vel = aVel + u_Accelerate;
	out_T -= u_DeltaTime;
	gl_PointSize = (1.0f - pos.z / pos.w) * u_VertexSize;
	gl_Position = pos;	// scr coord
}