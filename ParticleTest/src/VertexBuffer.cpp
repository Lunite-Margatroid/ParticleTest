#include "pch.h"
#include "VertexBuffer.h"

LM::VertexBuffer::VertexBuffer(unsigned int size, void* data, GLenum usage):
	m_uSize(size),m_Usage(usage)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

LM::VertexBuffer::VertexBuffer():m_uSize(0)
{
	GLCall(glGenBuffers(1, &m_id));
}

LM::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void LM::VertexBuffer::Init(unsigned int size, void* data, GLenum usage)
{
	m_uSize = size;
	m_Usage = usage;
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, m_Usage));
}

void LM::VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void LM::VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int LM::VertexBuffer::GetID() const
{
	return m_id;
}

size_t LM::VertexBuffer::GetSize() const
{
	return m_uSize;
}

void LM::VertexBuffer::SetData(unsigned int offset, unsigned int size, void* data)
{
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}
