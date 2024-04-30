#version 450 core

out vec4 FragColor;
in float ExistTime;

uniform vec4 u_VertexColor;

void main()
{
	if(ExistTime <= 0)
		discard;
	vec2 temp = gl_PointCoord - vec2(0.5f);
	float f = dot(temp, temp);
	if(f > 0.25)
	{
		discard;
	}
	
	FragColor = u_VertexColor;
}