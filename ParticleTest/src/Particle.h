#pragma once
#include "tfBuffer.h"
#include "VertexArray.h"
#include "Feedback.h"

namespace ptt
{
	class Particle
	{
	protected:
		LM::tfBuffer m_buffer;		// buffer obejct  vertex attrib
		LM::VertexArray m_VAO;		// vertex array object
		Feedback m_Feedback;		// transform feedback object

		int m_BufferOffset;			// buffer offset when offset    µ¥Î»:vertex

		int m_ParticleNum;
		bool m_AngleLimite;
		float m_AngleRangeX[2];
		float m_AngleRangeY[2];
		float m_VelocityRange[2];
	public:
		Particle();
		~Particle();

		virtual void Init();
		virtual void Update(float DeltaTime);
		virtual void Draw();
		virtual void PushAttrib(int dimension);
		virtual void ApplyAttrib();
		virtual void BindProgram(unsigned int program);

	};
}