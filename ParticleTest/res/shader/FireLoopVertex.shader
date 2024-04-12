#version 450 core
layout(location = 0) in float aT;
layout(location = 1) in vec3 aPos;
layout(location = 2) in float aVel;

uniform mat4 u_MVPTrans;
uniform float u_DeltaTime;

uniform float u_MinVelocity;
uniform float u_MaxVelocity;
uniform float u_MinAngleX;
uniform float u_MinAngleY;
uniform float u_MaxAngleX;
uniform float u_MaxAngleY;
uniform float u_MinTime;
uniform float u_MaxTime;


out float out_T;
out vec3 out_Pos;
out vec3 out_Vel;

void main()
{
	out_Pos = aPos + aVel;
	out_Vel = aVel;
	
	vec4 pos = vec4(out_Pos, 1.0f);
	gl_Position = u_MVPTrans * pos;
	if()
	out_T = aT - u_DeltaTime;
}