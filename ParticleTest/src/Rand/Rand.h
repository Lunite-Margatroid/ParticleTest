#pragma once

namespace ptt::myrand
{
	float GetRandFloat(float low, float high);
	float GetRandFloat(const float* range);
	float GetRandFloat();
	void GetRandUnitVec3(float* vec);
	void GetUniformUnitSphere(float* vec, int i, int N);

	template<typename T>
	void GenerateNormalDistribution(T* arr, int n, T mu, T sigma)
	{
		std::default_random_engine gen;
		std::normal_distribution<T> norDistribution(mu, sigma);
		for (int i = 0; i < n; i++)
		{
			arr[i] = norDistribution(gen);
		}
	}
}