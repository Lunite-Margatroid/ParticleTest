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
		m_VB.Init(300 * 300 * 3 * sizeof(float), vertice, GL_DYNAMIC_DRAW);
		
		//glBufferSubData(GL_ARRAY_BUFFER, 0, 300 * 300 * 3 * sizeof(float), vertice);

		delete[] vertice;

		/*m_VerticeNum = 30 * 30;
		float* vertice = new float[30 * 30 * 3];
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				vertice[i * 30 * 3 + j * 3] = -15.0f + 1.f * i;
				vertice[i * 30 * 3 + j * 3 + 1] = -15.0f + 1.f * j;
				vertice[i * 30 * 3 + j * 3 + 2] = (i + j) * PI / 15;
			}
		}
		m_VB.Init(30 * 30 * 3 * sizeof(float), vertice, GL_DYNAMIC_DRAW);*/

		//delete[] vertice;
	}
	void SinWave::InitVertexArray()
	{
		m_VA.SetVB(m_VB.GetID());
		m_VA.PushAttrib<float>(2);
		m_VA.PushAttrib<float>(1);
		m_VA.ApplyLayout();
		m_VA.SetMetaType(GL_POINTS);
	}
	void SinWave::InitFeedback()
	{
		m_Feedback.BindBuffer(0, m_VB.GetID());
		m_Feedback.BindBufferRange(0, m_VB.GetID(), 0, m_VB.GetSize());
		m_Feedback.PushVarying("gl_SkipComponent2");
		m_Feedback.PushVarying("out_T");
		m_Feedback.ApplyVarying(m_Shader.GetShaderID());
	}
	void SinWave::Init()
	{
		InitVertexBuffer();
		InitVertexArray();
		InitFeedback();
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
		m_Feedback.BeginTransformFeedback(GL_POINTS);
		SetShaderUniform();
		m_VA.DrawArray(m_VerticeNum);
		m_Feedback.EndTransformFeedback();
	}
	void SinWave::Update(float deltaTime)
	{
		m_Camera.Update(deltaTime);
	}
}


