#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in float aT;
layout(location = 2) in vec3 aVel;


uniform mat4 u_MVPTrans;
uniform mat4 u_MVTrans;
uniform float u_DeltaTime;

uniform float u_VertexSize;
uniform vec3 u_Accelerate;
uniform float u_kDF;
uniform float u_Far;


out vec3 out_Pos;
out vec3 out_Vel;
out float out_T;

out float ExistTime;


void main()
{
	vec4 cPos = u_MVTrans * vec4(aPos, 1.0f);
	vec4 pos = u_MVPTrans * vec4(aPos, 1.0f);

	out_Pos = aPos + aVel * u_DeltaTime;
	vec3 vel = aVel;
	vel = vel * abs(vel) * u_kDF;
	out_Vel = aVel + (u_Accelerate - vel) * u_DeltaTime;

	out_T = aT - u_DeltaTime;
	ExistTime = aT;


	if (cPos.z < 0)
	{
		gl_PointSize = max((1.0f + cPos.z / u_Far) * u_VertexSize, 1.0f);
	}
	//gl_PointSize = (1.0f - pos.z / pos.w)* 0.5f * u_VertexSize;
	gl_Position = pos;	// scr coord
}