#include "pch.h"
#include "Rand.h"

namespace ptt::myrand
{
	float GetRandFloat(float low, float high)
	{
		ASSERT(low <= high);
		return (float)(rand()) / RAND_MAX * (high - low) + low;
	}
	float GetRandFloat(const float* range)
	{
		return GetRandFloat(range[0], range[1]);
	}
	float GetRandFloat()
	{
		return (float)(rand()) / RAND_MAX;
	}
	void GetRandUnitVec3(float* vec)
	{
		ASSERT(vec);
		float u = GetRandFloat() * 2 -1;
		float theta = GetRandFloat() * 2 * PI;
		vec[2] = u;
		u = sqrtf(1 - u * u);
		vec[0] = u * cosf(theta);
		vec[1] = u * sinf(theta);
	}
	void GetUniformUnitSphere(float* vec, int i, int N)
	{
		float u = float(2 * i - 1) / N - 1;
		double theta = 2 * PI * i * 0.618;
		vec[2] = u;		// z
		u = sqrtf(1 - u*u);
		vec[0] = u * cos(theta);	// x
		vec[1] = u * sin(theta);	// y
	}
}