#include "pch.h"
#include "tfBuffer.h"

namespace LM
{
	tfBuffer::tfBuffer()
	{
	}
	tfBuffer::tfBuffer(unsigned int size, void* data,GLenum  usage)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	}
	tfBuffer::~tfBuffer()
	{
	}
	void tfBuffer::Init(unsigned int size, void* data, GLenum usage)
	{
		//GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_id));
		//GLCall(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, size, data, usage));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	}
	void tfBuffer::BindTotfb()
	{
		GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_id));
	}
	void tfBuffer::Unbindtfb()
	{
		GLCall(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0));
	}
}