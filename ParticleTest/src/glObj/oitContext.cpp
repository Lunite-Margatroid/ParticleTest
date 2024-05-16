#include "pch.h"
#include "oitContext.h"
#include "Application.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	void oitContext::InitDrawBuffer()
	{
		float indices[] =
		{
			-1.0f, -1.0f,
			1.0f, -1.0f,
			1.0f, 1.0f,
			-1.0f, 1.0f
		};
		m_vbo.Init(sizeof(indices), indices);
		m_vao.SetCount(4);
		m_vao.SetMetaType(GL_TRIANGLE_FAN);
		m_vao.SetVB(m_vbo.GetID());
		m_vao.PushAttrib<float>(2);
		m_vao.ApplyLayout();
	}
	oitContext::oitContext()
	{
		int pixelCount;
		char* data;
		std::pair<int, int> sceneFramebufferSize = Application::GetSceneFramebufferSize();
		m_Width = sceneFramebufferSize.first;
		m_Height = sceneFramebufferSize.second;
		pixelCount = m_Width * m_Height;
		/*----------------���� ͷָ�뻺��------------*/
		glGenTextures(1, &m_HeadMat);
		glBindTexture(GL_TEXTURE_2D, m_HeadMat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0,
			GL_R32UI,
			m_Width, m_Height,
			0,
			GL_RED_INTEGER,
			GL_UNSIGNED_INT,
			NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*----------------���� ͷָ���ʼ�� ����------------*/
		GLCall(glGenBuffers(1, &m_HeadInitializer));
		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_HeadInitializer));
		GLCall(glBufferData(GL_PIXEL_UNPACK_BUFFER, pixelCount * sizeof(GLuint), NULL, GL_STATIC_DRAW));
		GLCall(data = (char*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
		memset(data, 0xff, pixelCount * sizeof(GLuint));
		GLCall(glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER));
		//data = new char[pixelCount * sizeof(GLuint)];
		//memset(data, 0xff, pixelCount * sizeof(GLuint));
		//GLCall(glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, pixelCount * sizeof(GLuint), (void*)data));
		//delete[] data;
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		/*--------------------����ԭ�Ӽ�����----------------------*/
		glGenBuffers(1, &m_AtomicCounter);
		glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, m_AtomicCounter);
		glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_COPY);
		glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
		/*------------------------ ������ɫ��ϻ��� -------------------------*/
		GLCall(glGenBuffers(1, &m_ListBuffer));
		GLCall(glBindBuffer(GL_TEXTURE_BUFFER, m_ListBuffer));
		GLCall(glBufferData(GL_TEXTURE_BUFFER, 4 * 128 * pixelCount, NULL, GL_DYNAMIC_COPY));
		GLCall(glBindBuffer(GL_TEXTURE_BUFFER, 0));

		GLCall(glGenTextures(1, &m_ListTex));
		GLCall(glBindTexture(GL_TEXTURE_BUFFER, m_ListTex));
		GLCall(glTextureBuffer(m_ListTex, GL_RGBA32UI, m_ListBuffer));
		GLCall(glBindBuffer(GL_TEXTURE_BUFFER, 0));

		InitDrawBuffer();

	}

	oitContext::~oitContext()
	{
		glDeleteTextures(1, &m_HeadMat);
		glDeleteBuffers(1, &m_HeadInitializer);
		glDeleteBuffers(1, &m_AtomicCounter);
		glDeleteBuffers(1, &m_ListBuffer);
		glDeleteTextures(1, &m_ListTex);
	}
	void oitContext::RenderPreproc()
	{
		/*----------- ���ͷָ�뻺�� --------------*/
		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_HeadInitializer));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_HeadMat));
		GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0,
			0,0,
			m_Width, m_Height,
			GL_RED_INTEGER,
			GL_UNSIGNED_INT,
			NULL));
		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		/*--------------- ��ͷָ�뻺��󶨵�����Ԫ --------------*/
		glBindImageTexture(1,				// ����Ԫ
			m_HeadMat,		// ����ͼ�����
			0,				// mipmap level
			GL_FALSE,		// �Ƿ�ֲ�
			0,
			GL_READ_WRITE,	// ��дȨ��
			GL_R32UI);		// ��ͨ��32λ����
		/*---------------------ԭ�Ӽ���������----------------*/
		GLCall(glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, m_AtomicCounter));
		const GLuint zero = 0;
		GLCall(glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(zero), &zero));

		/*-------------- ��List����󶨵���Ӧ����Ԫ ---------------*/
		GLCall(glBindImageTexture(0,
			m_ListTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI));
	}
	void oitContext::Render()
	{
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::OIT);

		shader->Bind();
		/*--------------- ��ͷָ�뻺��󶨵�����Ԫ --------------*/
		glBindImageTexture(1,				// ����Ԫ
			m_HeadMat,		// ����ͼ�����
			0,				// mipmap level
			GL_FALSE,		// �Ƿ�ֲ�
			0,
			GL_READ_ONLY,	// ��дȨ��
			GL_R32UI);		// ��ͨ��32λ����
		/*-------------- ��List����󶨵���Ӧ����Ԫ ---------------*/
		GLCall(glBindImageTexture(0,
			m_ListTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI));

		m_vao.DrawArray();
	}
}