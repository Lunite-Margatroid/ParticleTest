#include "pch.h"
#include "ElementBuffer.h"

LM::ElementBuffer::ElementBuffer(unsigned int count, void* data, GLenum usage)
	:m_uCount(count)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));
}

LM::ElementBuffer::ElementBuffer() :m_uCount(0)
{
	GLCall(glGenBuffers(1, &m_id));
}

LM::ElementBuffer::~ElementBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void LM::ElementBuffer::Init(unsigned int count, void* data, GLenum usage)
{
	m_uCount = count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));
}

void LM::ElementBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void LM::ElementBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int LM::ElementBuffer::GetID() const
{
	return m_id;
}

unsigned int LM::ElementBuffer::GetCount() const
{
	return m_uCount;
}
