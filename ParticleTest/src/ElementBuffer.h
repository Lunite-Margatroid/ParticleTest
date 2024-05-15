#pragma once

namespace LM
{
	class ElementBuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_uCount;
	public:
		ElementBuffer(unsigned int count, void* data, GLenum usage  = GL_STATIC_DRAW);
		ElementBuffer();
		virtual ~ElementBuffer();

		void Init(unsigned int count, void* data, GLenum usage = GL_STATIC_DRAW);

		void Bind() const;
		void Unbind() const;

		unsigned int GetID() const;
		unsigned int GetCount() const;
	};
}