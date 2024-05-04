#include "pch.h"
#include "VertexArray.h"

namespace LM
{
	const bool AttribLayout::skip_attrib = true;

	VertexArray::VertexArray(GLenum type)
		:m_stride(0), m_MetaType(type), m_vb(0), m_eb(0)
	{
		GLCall(glGenVertexArrays(1, &m_id));
		Bind();
	}

	VertexArray::VertexArray(unsigned int vb, unsigned int eb, GLenum type)
		:m_vb(vb), m_eb(eb)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
		GLCall(glGenVertexArrays(1, &m_id));
		Bind();
	}


	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_id));
	}

	void VertexArray::ApplyLayout(unsigned int bufferOffset)
	{
		int i = 0;
		unsigned int offset = bufferOffset;
		if (m_eb != 0u)
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eb));
		}
		if (m_vb != 0u)
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
		}
		Bind();
		for (auto& attr : m_attribLayout)
		{
			if (!attr.skip)
			{
				GLCall(glVertexAttribPointer(i, attr.count, attr.type, attr.bNormalize, \
					m_stride, (void*)offset));
				GLCall(glEnableVertexAttribArray(i));
				i++;
			}
			offset += AttribLayout::GetSizeOfElem(attr.type) * attr.count;
		}
	}

	void VertexArray::ApplyLayoutSeparate(int numOfVertice)
	{
		int i = 0;
		unsigned int offset = 0;
		if (m_eb != 0u)
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eb));
		}
		if (m_vb != 0u)
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
		}
		Bind();
		for (auto& attr : m_attribLayout)
		{
			if (!attr.skip)
			{
				glVertexAttribPointer(i, attr.count, attr.type, attr.bNormalize, \
					AttribLayout::GetSizeOfElem(attr.type) * attr.count, (void*)(offset * numOfVertice));
				glEnableVertexAttribArray(i);
				i++;
			}
			offset += AttribLayout::GetSizeOfElem(attr.type) * attr.count;
		}
	}

	unsigned int VertexArray::GetID() const
	{
		return m_id;
	}

	GLenum VertexArray::GetMetaType() const
	{
		return m_MetaType;
	}

	void VertexArray::SetMetaType(GLenum metaType)
	{
		m_MetaType = metaType;
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_id));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

	void VertexArray::DrawElement(unsigned int count, unsigned int offset) const
	{
		Bind();
		GLCall(glDrawElements(m_MetaType, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int))));
	}

	void VertexArray::DrawElement(unsigned int count, unsigned int offset)
	{
		Bind();
		GLCall(glDrawElements(m_MetaType, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int))));
	}

	void VertexArray::DrawArray(unsigned int count, unsigned int offset) const
	{
		Bind();
		GLCall(glDrawArrays(m_MetaType, offset, count));
	}

	void VertexArray::DrawArray(unsigned int count, unsigned int offset)
	{
		Bind();
		GLCall(glDrawArrays(m_MetaType, offset, count));
	}


	void VertexArray::SetVB(unsigned int vb)
	{
		m_vb = vb;
	}

	void VertexArray::SetEB(unsigned int eb)
	{
		m_eb = eb;
	}
}

