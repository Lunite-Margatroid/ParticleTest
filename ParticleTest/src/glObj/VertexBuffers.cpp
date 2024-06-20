#include "pch.h"
#include "VertexBuffers.h"

namespace ptt
{
	VertexBuffers::VertexBuffers()
	{
		m_Capacity = 4 * 1024 * 1024;
		VertexBuffer::Init(m_Capacity, NULL, GL_STATIC_DRAW);
		m_uSize = 0;
	}
	VertexBuffers::VertexBuffers(GLenum usage)
	{
		m_Capacity = 4 * 1024 * 1024;
		VertexBuffer::Init(m_Capacity, NULL, usage);
		m_uSize = 0;
	}
	VertexBuffers::VertexBuffers(size_t size, GLenum usage)
	{
		m_Capacity = size;
		VertexBuffer::Init(m_Capacity, NULL, usage);
		m_uSize = 0;
	}
	size_t VertexBuffers::GetCapacity() const
	{
		return m_Capacity;
	}
	size_t VertexBuffers::Expand(size_t addCapacity)
	{// 扩容前的大小
		size_t ret = m_Capacity;

		/*------------ copy and store------------*/
		unsigned int copyBuffer;
		glGenBuffers(1,&copyBuffer);
		glBindBuffer(GL_COPY_WRITE_BUFFER, copyBuffer);
		glBufferData(GL_COPY_WRITE_BUFFER, m_uSize, NULL, GL_STREAM_READ);
		glCopyNamedBufferSubData(m_id, copyBuffer, 0, 0, m_uSize);
		
		/*------------- expand ------------------*/
		m_Capacity += addCapacity;
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, m_Capacity, NULL, GL_STATIC_DRAW);
		
		/*------------- copy ------------------*/
		glCopyNamedBufferSubData(copyBuffer, m_id, 0, 0, m_uSize);

		/*-------------delete temp buffer------*/
		glDeleteBuffers(1, &copyBuffer);

		return ret;
	}
	size_t VertexBuffers::PushBack(void* data, size_t size)
	{
		size_t ret = m_uSize;
		if (m_uSize + size <= m_Capacity)
		{
			
			SetData(m_uSize, size, data);
			m_uSize += size;
			return ret;
		}
		size_t addCapacity = (size + m_uSize) * 3 / 2 - m_Capacity;
		Expand(addCapacity);
		SetData(m_uSize, size, data);
		m_uSize += size;
		return ret;
	}
	size_t VertexBuffers::Clear()
	{
		size_t ret = m_uSize;
		m_uSize = 0;
		return ret;
	}
}