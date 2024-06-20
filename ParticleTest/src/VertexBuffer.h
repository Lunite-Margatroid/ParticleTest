#pragma once

namespace LM
{
	class VertexBuffer
	{
	protected:
		unsigned int m_id;
		size_t m_uSize;
		GLenum m_Usage;
	public:
		VertexBuffer(unsigned int size, void* data, GLenum usage = GL_STATIC_DRAW);
		VertexBuffer();
		virtual ~VertexBuffer();

		virtual void Init(unsigned int size, void* data, GLenum usage = GL_STATIC_DRAW);

		virtual void Bind() const;
		virtual void Unbind() const;

		unsigned int GetID() const;
		size_t GetSize() const;

		void SetData(unsigned int offset, unsigned int size, void*data);

	};
}