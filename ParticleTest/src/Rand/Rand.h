#pragma once

namespace ptt::myrand
{
	float GetRandFloat(float low, float high);
	float GetRandFloat(const float* range);
	float GetRandFloat();
	void GetRandUnitVec3(float* vec);
	void GetUniformUnitSphere(float* vec, int i, int N);
}