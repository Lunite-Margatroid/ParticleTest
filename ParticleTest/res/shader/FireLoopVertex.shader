#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aVel;
layout(location = 2) in float aT;

uniform mat4 u_MVPTrans;
uniform float u_DeltaTime;

uniform vec3 u_Position;

uniform float u_MinVelocity;
uniform float u_MaxVelocity;
uniform float u_MinAngleX;
uniform float u_MinAngleY;
uniform float u_MaxAngleX;
uniform float u_MaxAngleY;
uniform float u_MinTime;
uniform float u_MaxTime;


out float out_T;
out vec3 out_Pos;
out vec3 out_Vel;

float Float3ToRandFloat(vec3 value, float a, vec3 b)
{
	vec3 smallValue = sin(value);
	float random = dot(smallValue, b);
	random = fract(sin(random) * a);
	return random;
}

float Float3ToRandFloat(vec3 value)
{
	vec3 smallValue = sin(value);
	float random = dot(smallValue, vec3(89.786, 31.901, 78.314));
	random = fract(sin(random) * 14111.234);
	return random;
}


float FloatToRandFloat(float value,float a, float b)
{
	float random = fract(sin(value + b) * a);
	return random;
}

float FloatToRandFloat(float value)
{
	float random = fract(sin(value + 432.3115) * 12985.3214);
	return random;
}

/*
vec3 Float3ToRandFloat3(vec3 value)
{
	vec3 random = 
	vec3
	(
		Float3ToRandFloat(value, 13245.1234, vec3(32.432, 36.324, 97.321),
		Float3ToRandFloat(value, 14364.9836, vec3(52.321, 89.432, 32.231),
		Float3ToRandFloat(value, 13712.4782, vec3(53.432, 42.453, 54.531)
	);
	return random;
}
*/

float ReNormalized(float value, float minValue, float maxValue)
{
	return value * (maxValue - minValue) + minValue;
}

vec3 ReNormalized(vec3 value, float minValue, float maxValue)
{
	return value * (maxValue - minValue) + minValue;
}

void main()
{
	vec4 pos = vec4(aPos, 1.0f);	
	gl_Position = u_MVPTrans * pos;	// scr coord
	if(aT <= 0.0f)	// particle will dispear
	{	// Gen new particle
		float random = Float3ToRandFloat(aPos);
		float angleX;
		float angleY;
		float velocity;
		float time;
		angleX = ReNormalized(random, u_MinAngleX, u_MaxAngleX);
		random = FloatToRandFloat(random);
		
		angleY = ReNormalized(random, u_MinAngleY, u_MaxAngleY);
		random = FloatToRandFloat(random);
		
		velocity = ReNormalized(random, u_MinVelocity, u_MaxVelocity);
		random = FloatToRandFloat(random);
		
		time = ReNormalized(random, u_MinTime, u_MaxTime);
		
		// out_Vel
		float temp = sin(angleY) * velocity;
		out_Vel.x =  cos(angleX) * temp;
		out_Vel.y = cos(angleY) * velocity;
		out_Vel.z = sin(angleX) * temp;
		// out_Pos
		out_Pos = u_Position;
		// out_T
		out_T = time;
		return ;
	}
	out_Pos = aPos + aVel;	// Pos update
	out_Vel = aVel;			// vel update
	out_T = aT - u_DeltaTime;	// time update
}