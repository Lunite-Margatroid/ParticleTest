#pragma once
#include "VertexBuffer.h"

namespace LM
{
	class tfBuffer:public VertexBuffer
	{
	protected:

	public:
		tfBuffer();
		tfBuffer(unsigned int size, void* data = NULL, GLenum  usage = GL_DYNAMIC_COPY);
		~tfBuffer();

		virtual void Init(unsigned int size, void* data = NULL, GLenum usage = GL_DYNAMIC_COPY)override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};
}