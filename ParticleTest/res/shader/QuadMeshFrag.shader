#version 450 core

in vec2 TexCoord;
in vec4 FragCoord;
in vec3 NormalVec;

uniform vec4 u_MeshColor;

out vec4 FragColor;

float fuzz = 0.03f;
const float c_fuzz = 0.03f;
float dist;

float CoordToStrength(float u)
{
	
	u = fract(u);
	float frac1 = clamp((1.0f - u) / fuzz, 0.0f, 1.0f);
	float frac2  =clamp(u / fuzz, 0.0f, 1.0f);
	frac1 = frac1 < frac2? frac1 : frac2;
	frac1 = frac1 * frac1 * (3.0f - 2.0f * frac1);
	return 1.0f - frac1;
	
}

float SampleBias()
{
	float bias = dist / 750.f;
	return bias;
}

float CoordToStrength2D(float u, float v)
{
	u  =CoordToStrength(u);
	v  =CoordToStrength(v);
	return max(u, v);
}

void main()
{
	dist = length(FragCoord);
	
	float samRate = abs(dot(normalize(vec3(FragCoord)),NormalVec));
	samRate = samRate * 0.99f + 0.01f;
	
	fuzz = clamp((dist / 750.f) / samRate, c_fuzz, 0.5f);
	
	float lightRate = c_fuzz / fuzz;
	lightRate = 1.1f * lightRate / (0.1f + lightRate);
	float u = TexCoord.x;
	float v = TexCoord.y;
	float bias = SampleBias();
	mat3 samMatU = mat3(
		u - bias,	u,	u+bias,
		u - bias,	u,	u+bias,
		u - bias,	u,	u+bias
	);
	
	mat3 samMatV = mat3(
		v - bias,v - bias,v - bias,
		v ,v ,v,
		v + bias,v + bias,v + bias
	);
	
	
	float sum = 0;
	for(int i =0;i<3;i++)
		for(int j =0;j<3;j++)
		{
			sum += CoordToStrength2D(
				samMatU[i][j],
				samMatV[i][j]
			);
		}
	sum /= 9.0f;
	FragColor = mix(
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		u_MeshColor * lightRate,
		sum
	);
	
	//FragColor = vec4(1.0f ,1.0f, 1.0f ,1.0f);
}