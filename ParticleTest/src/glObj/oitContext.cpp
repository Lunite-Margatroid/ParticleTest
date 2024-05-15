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
		Application::GetDefaultFrameBufferSize(&m_Width, &m_Height);
		pixelCount = m_Width * m_Height;
		/*----------------���� ͷָ�뻺��------------*/
		glGenTextures(1, &m_HeadMat);
		glBindTexture(GL_TEXTURE_2D, m_HeadMat);
		glTexImage2D(GL_TEXTURE_2D, 0,
			GL_R32UI,
			m_Width, m_Height,
			0,
			GL_RED_INTEGER,
			GL_UNSIGNED_INT,
			NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*----------------���� ͷָ���ʼ�� ����------------*/
		glGenBuffers(1, &m_HeadInitializer);
		glBindTexture(GL_PIXEL_UNPACK_BUFFER, m_HeadInitializer);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, pixelCount * sizeof(GLuint), NULL, GL_STATIC_DRAW);
		//data = (GLuint*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
		//memset(data, 0xff, pixelCount * sizeof(GLuint));
		//glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
		data = new char[pixelCount * sizeof(GLuint)];
		memset(data, 0xff, pixelCount * sizeof(GLuint));
		glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, pixelCount * sizeof(GLuint), (void*)data);
		delete[] data;
		glBindTexture(GL_PIXEL_UNPACK_BUFFER, 0);
		/*--------------------����ԭ�Ӽ�����----------------------*/
		glGenBuffers(1, &m_AtomicCounter);
		glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, m_AtomicCounter);
		glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_COPY);
		glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
		/*------------------------ ������ɫ��ϻ��� -------------------------*/
		glGenBuffers(1, &m_ListBuffer);
		glBindBuffer(GL_TEXTURE_BUFFER, m_ListBuffer);
		glBufferData(GL_TEXTURE_BUFFER, 4 * 128 * pixelCount, NULL, GL_DYNAMIC_COPY);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		InitDrawBuffer();
	}

	oitContext::~oitContext()
	{
		glDeleteBuffers(4,(GLuint*)this);
	}
	void oitContext::RenderPreproc()
	{
		/*----------- ���ͷָ�뻺�� --------------*/
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_HeadInitializer);
		glBindTexture(GL_TEXTURE_2D, m_HeadMat);
		glTexImage2D(GL_TEXTURE_2D, 0,
			GL_R32UI,
			m_Width, m_Height,
			0,
			GL_RED_INTEGER,
			GL_UNSIGNED_INT,
			NULL);

		/*--------------- ��ͷָ�뻺��󶨵�����Ԫ --------------*/
		glBindImageTexture(1,				// ����Ԫ
			m_HeadMat,		// ����ͼ�����
			0,				// mipmap level
			GL_FALSE,		// �Ƿ�ֲ�
			0,
			GL_READ_WRITE,	// ��дȨ��
			GL_R32UI);		// ��ͨ��32λ����

		/*---------------------ԭ�Ӽ���������----------------*/
		glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, m_AtomicCounter);
		const GLuint zero = 0;
		glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(zero), &zero);

		/*-------------- ��List����󶨵���Ӧ����Ԫ ---------------*/
		glBindImageTexture(0,
			m_ListBuffer, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI);
	}
	void oitContext::Render()
	{
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::OIT);

		shader->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_HeadMat);
		shader->SetUniformTexture("head_pointer_image", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, m_ListBuffer);
		shader->SetUniformTexture("list_buffer", 1);

		GLboolean depthEnable = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		m_vao.DrawArray();
		if (depthEnable)
			glEnable(GL_DEPTH_TEST);
	}
}