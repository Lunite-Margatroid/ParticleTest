#pragma once

namespace LM
{
	class VertexBuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_uSize;
	public:
		VertexBuffer(unsigned int size, void* data);
		VertexBuffer();
		virtual ~VertexBuffer();

		void Init(unsigned int size, void* data);
		void Init(unsigned int size, void* data, GLenum usage);

		void Bind() const;
		void Unbind() const;

		unsigned int GetID() const;
		unsigned int GetSize() const;

	};
}