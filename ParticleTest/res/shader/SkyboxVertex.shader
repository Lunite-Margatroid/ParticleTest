#version 450 core
layout(location = 0)in vec3 aPos;

out vec3 SampleVec;


void main()
{
	SampleVec = aPos;
	gl_Position = vec4(aPos, 1.0f);
}