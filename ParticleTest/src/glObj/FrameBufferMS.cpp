#include "pch.h"
#include "FrameBufferMS.h"

LM::FrameBufferMS::FrameBufferMS(int width, int height, unsigned char nSample, unsigned char index)
	:m_nSample(nSample)
{
	m_width = width;
	m_height = height;
	m_texIndex = index;

	// ����֡�������
	GLCall(glGenFramebuffers(1, &m_fboID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

	// �����������
	// ��Ϊ��ɫ����
	GLCall(glGenTextures(1, &m_texID));
	GLCall(glActiveTexture(GL_TEXTURE0 + m_texIndex));
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_texID));
	GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_nSample,GL_RGB, 
		m_width, m_height, GL_TRUE));

	// ���û��Ʒ�ʽ�Ͳ�ֵ��ʽ
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// ������Ⱦ�������
	// ��Ϊ��Ȼ����ģ�滺��
	GLCall(glGenRenderbuffers(1, &m_rboID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rboID));
	GLCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_nSample,GL_DEPTH24_STENCIL8, m_width, m_height));

	// ������������Ⱦ����
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_texID, 0));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID));
	// ���������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		__debugbreak();
	}
}

void LM::FrameBufferMS::BlitFrameBuffer(const FrameBuffer& framebuffer)
{
	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_fboID));
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer.GetFrameBufferID()));
	GLCall(glBlitFramebuffer(0, 0,this->m_width, this->m_height,
		0, 0, framebuffer.GetWidth(), framebuffer.GetHeight(), 
		GL_COLOR_BUFFER_BIT, GL_NEAREST));
}

void LM::FrameBufferMS::BlitFrameBuffer(int defaultBufferWidth, int defaultBufferHeight)
{
	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_fboID));
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	GLCall(glBlitFramebuffer(0, 0,this->m_width, this->m_height,
		0, 0, defaultBufferWidth, defaultBufferHeight,
		GL_COLOR_BUFFER_BIT, GL_NEAREST));
}

void LM::FrameBufferMS::Init(int width, int height, unsigned char nSample, unsigned char index)
{
	m_width = width;
	m_height = height;
	m_texIndex = index;
	m_nSample = nSample;
	// ����֡�������
	GLCall(glGenFramebuffers(1, &m_fboID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

	// �����������
	// ��Ϊ��ɫ����
	GLCall(glGenTextures(1, &m_texID));
	GLCall(glActiveTexture(GL_TEXTURE0 + m_texIndex));
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_texID));
	GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_nSample, GL_RGB,
		m_width, m_height, GL_TRUE));

	// ���û��Ʒ�ʽ�Ͳ�ֵ��ʽ
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// ������Ⱦ�������
	// ��Ϊ��Ȼ����ģ�滺��
	GLCall(glGenRenderbuffers(1, &m_rboID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rboID));
	GLCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_nSample, GL_DEPTH24_STENCIL8, m_width, m_height));

	// ������������Ⱦ����
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_texID, 0));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID));
	// ���������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		__debugbreak();
	}
}
