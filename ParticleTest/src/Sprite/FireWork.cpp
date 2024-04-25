#include "pch.h"
#include "FireWork.h"

namespace ptt
{
	void FireWork::Init()
	{
		// position 3 float
		// velocity 3 float
		// exist time 1 float
		float* buffer = new float[m_Count * 7];
		size_t bufferSize = sizeof(float) * m_Count * 7;
		memset(buffer, 0, bufferSize);
		
		if (m_Distribution == Distribution::random)
		{
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 7);
				//temp[3]; // velocity x
				//temp[4]; // velocity y
				//temp[5]; // velocity z
				myrand::GetRandUnitVec3(temp + 3);
				temp[6] = myrand::GetRandFloat(m_TimeRange[0], m_TimeRange[1]); // time
			}
		}
		else // Distribution::uniform
		{
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 7);
				//temp[3]; // velocity x
				//temp[4]; // velocity y
				//temp[5]; // velocity z
				myrand::GetUniformUnitSphere(temp + 3, i, m_Count);
				temp[6] = myrand::GetRandFloat(m_TimeRange[0], m_TimeRange[1]); // time
			}
		}
		m_buffer[0].Init(bufferSize, buffer);
		m_buffer[1].Init(bufferSize, buffer);
		delete[] buffer;

		m_VAO[0].PushAttrib<float>(3);
		m_VAO[0].PushAttrib<float>(3);
		m_VAO[0].PushAttrib<float>(1);
		m_VAO[0].ApplyLayout();

		m_VAO[1].PushAttrib<float>(3);
		m_VAO[1].PushAttrib<float>(3);
		m_VAO[1].PushAttrib<float>(1);
		m_VAO[1].ApplyLayout();
	}
	FireWork::FireWork()
	{
	}
	FireWork::~FireWork()
	{
	}
	void FireWork::Update(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}
	void FireWork::Render(const glm::mat4& modelTrans)
	{
	}
	void FireWork::Reset()
	{
	}
	void FireWork::SetCount()
	{
	}
	void FireWork::SetVelocityRange(float low, float high)
	{
	}
	void FireWork::SetVelocityRange(const float* range)
	{
	}
	void FireWork::SetTimeRange(float low, float high)
	{

	}
	void FireWork::SetTimeRange(const float* range)
	{
	}
	void FireWork::SetAcceleration(const float* acc)
	{
	}
	void FireWork::SetDistribution(Distribution dtb)
	{
	}
	void FireWork::SetParticleCount(unsigned int count)
	{
	}
}
