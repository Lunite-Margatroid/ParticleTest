#include "pch.h"
#include "tfBuffer.h"

namespace LM
{
	tfBuffer::tfBuffer()
	{
	}
	tfBuffer::tfBuffer(unsigned int size, void* data,GLenum  usage)
	{
		GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_id));
		GLCall(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, size, data, usage));
	}
	tfBuffer::~tfBuffer()
	{
	}
	void tfBuffer::Init(unsigned int size, void* data, GLenum usage)
	{
		GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_id));
		GLCall(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, size, data, usage));
	}
	void tfBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_id));
	}
	void tfBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0));
	}
}