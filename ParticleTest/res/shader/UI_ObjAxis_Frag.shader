#version 450 core

in vec4 VertexColor;

out vec4 FragColor;

void main()
{
	FragColor = VertexColor;
}