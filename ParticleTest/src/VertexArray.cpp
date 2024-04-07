#include "pch.h"
#include "VertexArray.h"

LM::VertexArray::VertexArray(GLenum type)
	:m_stride(0),m_MetaType(type)
{
	GLCall(glGenVertexArrays(1, &m_id));
	Bind();
}

LM::VertexArray::VertexArray(unsigned int vb, unsigned int eb, GLenum type)
	:m_vb(vb),m_eb(eb)
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
	GLCall(glGenVertexArrays(1, &m_id));
	Bind();
}


LM::VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void LM::VertexArray::ApplyLayout()
{
	int i = 0;
	unsigned int offset = 0;
	if (m_eb)
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eb));
	if (m_vb)
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
	Bind();
	for (auto& attr : m_attribLayout)
	{
		glVertexAttribPointer(i, attr.count , attr.type, attr.bNormalize, \
			m_stride, (void*)offset);
		glEnableVertexAttribArray(i);

		offset += AttribLayout::GetSizeOfElem(attr.type) * attr.count;
		i++;
	}
}

unsigned int LM::VertexArray::GetID() const
{
	return m_id;
}

GLenum LM::VertexArray::GetMetaType() const
{
	return m_MetaType;
}

void LM::VertexArray::SetMetaType(GLenum metaType)
{
	m_MetaType = metaType;
}

void LM::VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_id));
}

void LM::VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void LM::VertexArray::DrawElement(unsigned int count, unsigned int offset) const
{
	Bind();
	glDrawElements(m_MetaType, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
}

void LM::VertexArray::DrawElement(unsigned int count, unsigned int offset)
{
	Bind();
	glDrawElements(m_MetaType, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
}

void LM::VertexArray::DrawArray(unsigned int count, unsigned int offset) const
{
	Bind();
	glDrawArrays(m_MetaType, offset, count);
}

void LM::VertexArray::DrawArray(unsigned int count, unsigned int offset)
{
	Bind();
	glDrawArrays(m_MetaType, offset, count);
}


void LM::VertexArray::SetVB(unsigned int vb)
{
	m_vb = vb;
}

void LM::VertexArray::SetEB(unsigned int eb)
{
	m_eb = eb;
}

