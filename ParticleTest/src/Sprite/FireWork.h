#pragma once
#include "Sprite.h"
#include "tfBuffer.h"
#include "VertexArray.h"
#include "Feedback.h"
#include "ColoredSprite.h"
#include "Rand/Rand.h"
namespace ptt
{
	class FireWork :public ColoredSprite<1>
	{
	public:
		// random 均匀随机分布
		// uniform 均匀排列
		enum class Distribution { random, uniform };
	protected:
		LM::tfBuffer m_buffer[2];		// buffer obejct  vertex attrib
		LM::VertexArray m_VAO[2];		// vertex array object
		Feedback m_Feedback;			// transform feedback object

		glm::vec3 m_Acc;
		float m_VelRange[2];
		float m_TimeRange[2];
		unsigned int m_Count;
		Distribution m_Distribution;

		float m_DeltaTime;

		void Init();
	public:
		

		FireWork();
		~FireWork();

		virtual void Update(float deltaTime);
		virtual void Render(const glm::mat4& modelTrans) override;

		virtual void Reset();

		void SetCount();
		void SetVelocityRange(float low, float high);
		void SetVelocityRange(const float* range);

		void SetTimeRange(float low, float high);
		void SetTimeRange(const float* range);

		void SetAcceleration(const float* acc);

		void SetDistribution(Distribution dtb);

		void SetParticleCount(unsigned int count);
	};


}