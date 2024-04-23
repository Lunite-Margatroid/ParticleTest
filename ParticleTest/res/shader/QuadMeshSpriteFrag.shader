#version 450 core

in vec2 TexCoord;

uniform vec4 u_MeshColor;

out vec4 FragColor;

float fuzz = 0.03f;
const float c_fuzz = 0.03f;


float CoordToStrength(float u)
{
	
	u = fract(u);
	float frac1 = clamp((1.0f - u) / fuzz, 0.0f, 1.0f);
	float frac2  =clamp(u / fuzz, 0.0f, 1.0f);
	frac1 = frac1 < frac2? frac1 : frac2;
	frac1 = frac1 * frac1 * (3.0f - 2.0f * frac1);
	return 1.0f - frac1;
	
}

float CoordToStrength2D(float u, float v)
{
	u = CoordToStrength(u);
	v = CoordToStrength(v);
	return max(u, v);
}

void main()
{
	
	//float samRate = abs(dot(normalize(FragCoord),NormalVec));
	//samRate = samRate * 0.99f + 0.01f;

	vec2 pw = fwidth(TexCoord);
	fuzz = clamp(max(pw.s, pw.t) * 2, c_fuzz, 1.0f);
	
	float lightRate = c_fuzz / fuzz;
	
	lightRate = 1.1f * lightRate / (0.1f + lightRate);
	
	float u = TexCoord.x;
	float v = TexCoord.y;
	float sum = CoordToStrength2D(u,v);
	
	vec3 temp = vec3(u_MeshColor);
	
	FragColor = mix(
		vec4(temp, 0.0f),
		u_MeshColor,
		sum
	) * lightRate;
	
	//FragColor = vec4(1.0f ,1.0f, 1.0f ,1.0f);
}