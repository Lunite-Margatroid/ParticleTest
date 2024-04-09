#version 450 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in float aT;

uniform mat4 u_MVPTrans;

out float out_T;

void main()
{
	vec4 pos = vec4(aPos, sin(aT), 1.0f);
	gl_Position = u_MVPTrans * pos;
}