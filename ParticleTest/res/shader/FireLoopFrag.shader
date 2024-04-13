#version 450 core

out vec4 FragColor;

uniform vec3 u_VertexColor;

void main()
{
	vec2 temp = gl_PointCoord - vec2(0.5f);
	float f = dot(temp, temp);
	if(f > 0.25)
	{
		discard;
	}
	
	FragColor = vec4(u_VertexColor, 1.0f);
}