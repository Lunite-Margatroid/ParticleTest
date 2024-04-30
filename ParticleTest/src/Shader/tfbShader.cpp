#include "pch.h"
#include "tfbShader.h"
namespace ptt
{
	void tfbShader::TransformFeedbackInit()
	{
		GLCall(glGenTransformFeedbacks(1, &m_tfbID));
	}
	tfbShader::tfbShader(const std::string& vertexShader, const std::string& fragmentShader):
		Shader(vertexShader, fragmentShader),
		m_Active(false),
		m_Pause(false)
	{
		TransformFeedbackInit();
	}
	tfbShader::tfbShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
		:Shader(vertexShader, fragmentShader, geometryShader),
		m_Active(false),
		m_Pause(false)
	{
		TransformFeedbackInit();
	}
	tfbShader::~tfbShader()
	{
		GLCall(glDeleteTransformFeedbacks(1, &m_tfbID));
	}


	void tfbShader::BindTransformFeedback()
	{
		GLCall(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_tfbID));
	}
	void tfbShader::UnbindTransformFeedback()
	{
		GLCall(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
	}
	unsigned int tfbShader::GetTransformFeedbackID() const
	{
		return m_tfbID;
	}
	void tfbShader::BindBuffer(unsigned int index, unsigned int buffer)
	{
		BindTransformFeedback();
		GLCall(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer));
	}
	void tfbShader::BindBufferRange(unsigned int index, unsigned int buffer, int offset, int size)
	{
		BindTransformFeedback();
		GLCall(glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer, offset, size));
		// GLCall(glTransformFeedbackBufferRange(m_tfbID, index, buffer, offset, size));
	}
	void tfbShader::ApplyVarying(GLenum bufferMode)
	{
		Bind();
		int count = m_Varyings.size();
		char** strs = NULL;
		if (count > 0)
			strs = m_Varyings.data();
		GLCall(glTransformFeedbackVaryings(m_ShaderID, count, strs, bufferMode));
		GLCall(glLinkProgram(m_ShaderID));
	}
	void tfbShader::PushVarying(const char* varying)
	{
		char* str = new char[strlen(varying) + 1];
		strcpy(str, varying);
		m_Varyings.push_back(str);
	}
	void tfbShader::BeginTransformFeedback(GLenum primitiveMode)
	{
		ASSERT(!m_Active);
		m_Active = true;
		m_Pause = false;
		GLCall(glBeginTransformFeedback(primitiveMode));
	}
	void tfbShader::EndTransformFeedback()
	{
		ASSERT(m_Active);
		m_Active = false;
		m_Pause = false;
		GLCall(glEndTransformFeedback());
	}
	void tfbShader::PauseTransformFeedback()
	{
		ASSERT(m_Active);
		ASSERT(!m_Pause);
		m_Pause = true;
		GLCall(glPauseTransformFeedback());
	}
	void tfbShader::ResumeTransformFeedback()
	{
		ASSERT(m_Pause);
		ASSERT(m_Active);
		m_Pause = false;
		GLCall(glResumeTransformFeedback());
	}
}