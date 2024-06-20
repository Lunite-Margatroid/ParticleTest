#version 450 core
in vec4 Color;
out vec4 FragColor;

#define POINTS 0
uniform int u_DrawMode;

void main()
{
	if(u_DrawMode == POINTS)
	{
		vec2 temp = gl_PointCoord - vec2(0.5f);
		float f = dot(temp, temp);
		if(f > 0.25)
		{
			discard;
		}
	}

	FragColor = Color;
}