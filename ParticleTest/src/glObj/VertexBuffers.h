#pragma once
#include "VertexBuffer.h"

namespace ptt
{
	class VertexBuffers : public LM::VertexBuffer
	{
	protected:
		size_t m_Capacity;
	public:
		VertexBuffers();
		VertexBuffers(GLenum usage);
		VertexBuffers(size_t size, GLenum usage);

		size_t GetCapacity() const;

		size_t Expand(size_t addCapacity);
		size_t PushBack(void *data, size_t size);
		size_t Clear();
	};
}