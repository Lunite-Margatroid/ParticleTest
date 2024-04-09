#include "pch.h"
#include "SinWave.h"

namespace ptt
{
	void SinWave::InitVertexBuffer()
	{
		m_VerticeNum = 300 * 300;
		float* vertice = new float[300 * 300 * 3];
		for (int i = 0; i < 300; i++)
		{
			for (int j = 0; j < 300; j++)
			{
				vertice[i * 300 * 3 + j * 3] = -15.0f + 0.1f * i;
				vertice[i * 300 * 3 + j * 3 + 1] = -15.0f + 0.1f * j;
				vertice[i * 300 * 3 + j * 3 + 2] = (i + j) * PI / 150;
			}
		}
		m_VB1.Init(300 * 300 * 3 * sizeof(float), vertice, GL_DYNAMIC_COPY);
		delete[] vertice;

		m_VB2.Init(300 * 300 * 3 * sizeof(float));

	}
	void SinWave::InitVertexArray()
	{
		m_VA1.SetVB(m_VB1.GetID());
		m_VA1.PushAttrib<float>(2);
		m_VA1.PushAttrib<float>(1);
		m_VA1.ApplyLayout();
		m_VA1.SetMetaType(GL_POINTS);

		m_VA2.SetVB(m_VB2.GetID());
		m_VA2.PushAttrib<float>(2);
		m_VA2.PushAttrib<float>(1);
		m_VA2.ApplyLayout();
		m_VA2.SetMetaType(GL_POINTS);
	}
	void SinWave::InitFeedback()
	{
		m_Feedback.PushVarying("out_Pos");
		m_Feedback.PushVarying("out_T");
		m_Feedback.ApplyVarying(m_Shader.GetShaderID());
	}
	void SinWave::Init()
	{
		InitVertexBuffer();
		InitVertexArray();
		InitFeedback();
		m_DeltaTime = 0.f;
	}
	void SinWave::SetShaderUniform()
	{
		static glm::mat4 viewTrans;
		static glm::mat4 projectionTrans;
		static glm::mat4 mvpTrans;

		viewTrans = m_Camera.GetViewTrans();
		projectionTrans = m_Camera.GetProjectionTrans();
		mvpTrans = projectionTrans * viewTrans;

		m_Shader.Bind();
		m_Shader.SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader.SetUniform1f("u_DeltaTime", m_DeltaTime);
	}
	SinWave::SinWave()
		:m_Shader("./res/shader/SinWaveVertex.shader", "./res/shader/SinWaveFrag.shader")
	{
		Init();
	}
	SinWave::~SinWave()
	{
	}
	void SinWave::Render()
	{
		SetShaderUniform();
		static int frontBuffer = 1;
		m_Feedback.Bind();
		if (frontBuffer == 1)
		{
			m_Feedback.BindBuffer(0, m_VB2.GetID());
			m_Feedback.BeginTransformFeedback(GL_POINTS);
			m_VA1.DrawArray(m_VerticeNum);
			m_Feedback.EndTransformFeedback();
			frontBuffer = 2;
		}
		else
		{
			m_Feedback.BindBuffer(0, m_VB1.GetID());
			m_Feedback.BeginTransformFeedback(GL_POINTS);
			m_VA2.DrawArray(m_VerticeNum);
			m_Feedback.EndTransformFeedback();
			frontBuffer = 1;
		}
		m_Feedback.Unbind();
	}
	void SinWave::Update(float deltaTime)
	{
		m_Camera.Update(deltaTime);
		m_DeltaTime = deltaTime;
	}
}


