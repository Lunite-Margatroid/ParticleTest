#pragma once

namespace LM
{
	class VertexBuffer
	{
	protected:
		unsigned int m_id;
		unsigned int m_uSize;
	public:
		VertexBuffer(unsigned int size, void* data);
		VertexBuffer();
		virtual ~VertexBuffer();

		virtual void Init(unsigned int size, void* data, GLenum usage = GL_STATIC_DRAW);

		virtual void Bind() const;
		virtual void Unbind() const;

		unsigned int GetID() const;
		unsigned int GetSize() const;

	};
}