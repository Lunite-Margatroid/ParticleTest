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

		size_t GetCapacity() const;

		size_t Expand(size_t addCapacity);
		size_t PushBack(void *data, size_t size);
	};
}