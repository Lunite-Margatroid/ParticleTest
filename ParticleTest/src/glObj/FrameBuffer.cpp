#include "pch.h"
#include "FrameBuffer.h"

LM::FrameBuffer::FrameBuffer()
	:m_fboID(0), m_texID(0), m_rboID(0),m_width(0), m_height(0), m_texIndex(0),m_AspectRatio(16.f / 9.f)
{
}

LM::FrameBuffer::FrameBuffer(int width, int height, unsigned char index)
	:m_width(width),m_height(height),m_texIndex(index)
{
	Init(m_width, m_height);
}

LM::FrameBuffer::~FrameBuffer()
{
	if(m_texID)
		GLCall(glDeleteTextures(1, &m_texID));
	if(m_rboID)
		GLCall(glDeleteRenderbuffers(1, &m_rboID));
	if(m_fboID)
		GLCall(glDeleteFramebuffers(1, &m_fboID));
}

void LM::FrameBuffer::Init(int width, int height)
{
	m_height = height;
	m_width = width;
	m_AspectRatio = (float)m_width / m_height;

	// ����֡�������
	GLCall(glGenFramebuffers(1, &m_fboID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

	// �����������
	// ��Ϊ��ɫ����
	GLCall(glGenTextures(1, &m_texID));
	GLCall(glActiveTexture(GL_TEXTURE0 + m_texIndex));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_INT, NULL));

	// ���û��Ʒ�ʽ�Ͳ�ֵ��ʽ
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// ������Ⱦ�������
	// ��Ϊ��Ȼ����ģ�滺��
	GLCall(glGenRenderbuffers(1, &m_rboID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rboID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height));

	// ������������Ⱦ����
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texID, 0));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID));
	// ���������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		__debugbreak();
	}

	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void LM::FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));
}

void LM::FrameBuffer::Unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

unsigned int LM::FrameBuffer::GetFrameBufferID() const
{
	return m_fboID;
}

unsigned int LM::FrameBuffer::GetTextureID() const
{
	return m_texID;
}

unsigned char LM::FrameBuffer::GetTexIndex() const
{
	GLCall(glActiveTexture(GL_TEXTURE0+m_texIndex));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));
	return m_texIndex;
}

int LM::FrameBuffer::GetWidth() const
{
	return m_width;
}

int LM::FrameBuffer::GetHeight() const
{
	return m_height;
}

float LM::FrameBuffer::GetAspectRatio() const
{
	return m_AspectRatio;
}

