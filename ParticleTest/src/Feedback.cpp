#include "pch.h"
#include "Feedback.h"

namespace ptt
{
	bool Feedback::s_Active = false;
	bool Feedback::s_Pause = false;

	void Feedback::Init()
	{
		GLCall(glGenTransformFeedbacks(1, &m_tfID));
	}
	Feedback::Feedback()
	{
		Init();
	}
	Feedback::~Feedback()
	{
		GLCall(glDeleteTransformFeedbacks(1, &m_tfID));
		for (char* strVarying : m_Varyings)
		{
			delete[] strVarying;
		}
	}
	void Feedback::Bind()
	{
		GLCall(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_tfID));
	}
	void Feedback::Unbind()
	{
		GLCall(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
	}
	unsigned int Feedback::GetTransformFeedbackID() const
	{
		return m_tfID;
	}
	void Feedback::BindBuffer(unsigned int index, unsigned int buffer)
	{
		Bind();
		GLCall(glTransformFeedbackBufferBase(m_tfID, index, buffer));
	}
	void Feedback::BindBufferRange(unsigned int index, unsigned int buffer, int offset, int size)
	{
		Bind();
		GLCall(glTransformFeedbackBufferRange(m_tfID, index, buffer,offset, size));
	}
	void Feedback::ApplyVarying(unsigned int program, GLenum bufferMode)
	{
		Bind();
		int count = m_Varyings.size();
		char** strs = NULL;
		if (count > 0)
			strs = m_Varyings.data();
		GLCall(glTransformFeedbackVaryings(program, count, strs, bufferMode));
		GLCall(glLinkProgram(program));
	}
	void Feedback::PushVarying(const char* varying)
	{
		char* str = new char[strlen(varying) + 1];
		strcpy(str, varying);
		m_Varyings.push_back(str);
	}
	void Feedback::BeginTransformFeedback(GLenum primitiveMode)
	{
		ASSERT(!s_Active);
		s_Active = true;
		s_Pause = false;
		GLCall(glBeginTransformFeedback(primitiveMode));
	}
	void Feedback::EndTransformFeedback()
	{
		ASSERT(s_Active);
		s_Active = false;
		s_Pause = false;
		GLCall(glEndTransformFeedback());
	}
	void Feedback::PauseTransformFeedback()
	{
		ASSERT(s_Active);
		ASSERT(!s_Pause);
		s_Pause = true;
		GLCall(glPauseTransformFeedback());
	}
	void Feedback::ResumeTransformFeedback()
	{
		ASSERT(s_Pause);
		ASSERT(s_Active);
		s_Pause = false;
		GLCall(glResumeTransformFeedback());
	}
}