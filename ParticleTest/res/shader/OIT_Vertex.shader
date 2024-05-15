#version 450 core
layout(location = 0) in vec2 aCoord;

void main()
{
	gl_Position = vec4(aCoord, 0.0f, 1.0f);
}
