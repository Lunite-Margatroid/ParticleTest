#pragma once
#include "tfBuffer.h"
#include "VertexArray.h"
#include "Feedback.h"
#include "Shader.h"

namespace ptt
{
	class Particle
	{
	protected:
		LM::tfBuffer m_buffer[2];		// buffer obejct  vertex attrib
		LM::VertexArray m_VAO[2];	// vertex array object
		Feedback m_Feedback;		// transform feedback object

		LM::Shader* m_Shader;
		unsigned int m_Program;		// shader program

		unsigned int m_BufferOffset;			// buffer offset when offset    µ¥Î»:vertex

		unsigned int m_ParticleNum;			// number of particle
		bool m_AngleLimite;			// if Angle is limited
		float m_AngleRangeX[2];		// Angle range for x axis
		float m_AngleRangeY[2];		// angle range for y axis
		float m_VelocityRange[2];	// velocity range
		float m_TimeRange[2];		// range of exist time

		static inline float GetRandFloat(float low, float high)
		{
			ASSERT(low <= high);
			return (float)(rand() )/ RAND_MAX * (high - low) + low;
		}
		static inline float GetRandFloat(const float* range)
		{
			return GetRandFloat(range[0], range[1]);
		}

		int BindBufferFeedback();
	public:
		Particle(LM::Shader* shader, int nParticle = 300);
		~Particle();

		void EnableAngleLimite();
		void DisableAngleLimite();
		void SetAngleRangeX(float low, float high);
		void SetAngleRangeY(float low, float high);
		void SetVelocityRange(float low, float high);
		void SetTimeRange(float low, float high);

		virtual void Init();
		virtual void Update(float DeltaTime);
		virtual void Draw();
		virtual void PushAttrib(int dimension);
		virtual void ApplyAttrib();
		virtual void BindProgram(unsigned int program);

		void InitShaderUniform();

	};
}