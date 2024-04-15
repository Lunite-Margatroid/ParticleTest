#version 450 core

in vec2 TexCoord;

uniform vec4 u_MeshColor;

out vec4 FragColor;

float fuzz = 0.03f;
float bias = 0.005f;

float CoordToStrength(float u)
{
	u = fract(u);
	float frac1 = clamp((1.0f - u) / fuzz, 0.0f, 1.0f);
	float frac2  =clamp(u / fuzz, 0.0f, 1.0f);
	frac1 = frac1 < frac2? frac1 : frac2;
	frac1 = frac1 * frac1 * (3.0f - 2.0f * frac1);
	return 1.0f - frac1;
	
}

void main()
{
	float u = CoordToStrength(TexCoord.x);
	float v = CoordToStrength(TexCoord.y);
	float sum = min(u + v, 1.0f);
	FragColor = mix(
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		u_MeshColor,
		sum
	);
	//FragColor = vec4(1.0f ,1.0f, 1.0f ,1.0f);
}