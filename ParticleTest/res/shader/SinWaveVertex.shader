#version 450 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in float aT;

uniform mat4 u_MVPTrans;
uniform float u_DeltaTime;
out float out_T;
out vec2 out_Pos;
void main()
{
	vec4 pos = vec4(aPos.x, sin(aT), aPos.y, 1.0f);
	gl_Position = u_MVPTrans * pos;
	out_T = aT + u_DeltaTime * 3.1416f;
	out_Pos = aPos;
}