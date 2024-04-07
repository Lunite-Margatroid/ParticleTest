#include "pch.h"
#include "Feedback.h"

namespace ptt
{
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
	unsigned int Feedback::GetTransformFeedbackID() const
	{
		return m_tfID;
	}
	void Feedback::BindBuffer(unsigned int index, unsigned int buffer)
	{
		GLCall(glTransformFeedbackBufferBase(m_tfID, index, buffer));
	}
	void Feedback::ApplyVarying(unsigned int program, GLenum bufferMode)
	{
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
		m_Varyings.push_back(str);
	}
}