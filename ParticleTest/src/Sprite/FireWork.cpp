#include "pch.h"
#include "FireWork.h"

namespace ptt
{
	void FireWork::Init()
	{
		// position 3 float
		// velocity 3 float
		// exist time 1 float
		float* buffer = new float[m_Count * 7];
		size_t bufferSize = sizeof(float) * m_Count * 7;
		memset(buffer, 0, bufferSize);
		
		if (m_Distribution == Distribution::random)
		{
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 7);
				//temp[3]; // velocity x
				//temp[4]; // velocity y
				//temp[5]; // velocity z
				myrand::GetRandUnitVec3(temp + 3);
				temp[6] = myrand::GetRandFloat(m_TimeRange[0], m_TimeRange[1]); // time
			}
		}
		else // Distribution::uniform
		{
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 7);
				//temp[3]; // velocity x
				//temp[4]; // velocity y
				//temp[5]; // velocity z
				myrand::GetUniformUnitSphere(temp + 3, i, m_Count);
				temp[6] = myrand::GetRandFloat(m_TimeRange[0], m_TimeRange[1]); // time
			}
		}
		m_buffer[0].Init(bufferSize, buffer);
		m_buffer[1].Init(bufferSize, buffer);
		delete[] buffer;

		m_VAO[0].SetVB(m_buffer[0].GetID());
		m_VAO[0].SetMetaType(GL_POINTS);
		m_VAO[0].PushAttrib<float>(3);
		m_VAO[0].PushAttrib<float>(3);
		m_VAO[0].PushAttrib<float>(1);
		m_VAO[0].ApplyLayout();

		m_VAO[1].SetVB(m_buffer[1].GetID());
		m_VAO[1].SetMetaType(GL_POINTS);
		m_VAO[1].PushAttrib<float>(3);
		m_VAO[1].PushAttrib<float>(3);
		m_VAO[1].PushAttrib<float>(1);
		m_VAO[1].ApplyLayout();
	}
	FireWork::FireWork(unsigned int count)
		:m_Acc(0.f),
		m_Count(count),
		m_Distribution(Distribution::uniform),
		m_DeltaTime(0.0f),
		m_BufferFlag(true),
		m_VertexSize(10.0f)
	{
		m_VelRange[0] = 4.9f;
		m_VelRange[1] = 5.f;
		m_TimeRange[0] = 1.9f;
		m_TimeRange[1] = 2.0f;
		m_Color[0] = glm::vec4(1.0f);
		Init();
	}
	FireWork::~FireWork()
	{
	}
	void FireWork::Update(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}
	void FireWork::Render(const glm::mat4& modelTrans)
	{
		tfbShader *shader = dynamic_cast<tfbShader*>(Renderer::GetShader(Renderer::Shaders::FireWork));
		ASSERT(shader!=nullptr);
		Camera* camera = Renderer::GetCurrentCamera();

		//glm::mat4& mvTrans = Renderer::GetMVTrans();
		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		//mvTrans = camera->GetViewTrans() * modelTrans;
		mvpTrans = camera->GetProjectionTrans() * camera->GetViewTrans() * modelTrans;

		shader->Bind();
		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		//shader->SetUniformMatrix4f("u_MVTrans",false, glm::value_ptr(mvTrans));
		shader->SetUniform1f("u_DeltaTime", m_DeltaTime);
		shader->SetUniform3f("u_Accelerate", &m_Acc.x);
		shader->SetUniform4f("u_VertexColor", &m_Color[0].r);
		shader->SetUniform1f("u_VertexSize", m_VertexSize);

		shader->BindTransformFeedback();
		if (m_BufferFlag)
		{
			shader->BindBuffer(0, m_buffer[0].GetID());
			shader->BeginTransformFeedback(GL_POINTS);
			m_buffer[1].Bind();
			m_VAO[1].DrawArray(m_Count);
			
		}
		else
		{
			shader->BindBuffer(0, m_buffer[1].GetID());
			m_buffer[0].Bind();
			shader->BeginTransformFeedback(GL_POINTS);
			m_VAO[0].DrawArray(m_Count);
		}
		shader->EndTransformFeedback();
		m_BufferFlag = !m_BufferFlag;
	}
	void FireWork::Reset()
	{
		float* buffer = new float[m_Count * 7];
		size_t bufferSize = sizeof(float) * m_Count * 7;
		memset(buffer, 0, bufferSize);

		if (m_Distribution == Distribution::random)
		{
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 7);
				//temp[3]; // velocity x
				//temp[4]; // velocity y
				//temp[5]; // velocity z
				myrand::GetRandUnitVec3(temp + 3);
				temp[6] = myrand::GetRandFloat(m_TimeRange[0], m_TimeRange[1]); // time
			}
		}
		else // Distribution::uniform
		{
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 7);
				//temp[3]; // velocity x
				//temp[4]; // velocity y
				//temp[5]; // velocity z
				myrand::GetUniformUnitSphere(temp + 3, i, m_Count);
				temp[6] = myrand::GetRandFloat(m_TimeRange[0], m_TimeRange[1]); // time
			}
		}
		m_buffer[0].SetData(0, bufferSize, buffer);
		m_buffer[1].SetData(0, bufferSize, buffer);
		delete[] buffer;
	}
	void FireWork::SetVelocityRange(float low, float high)
	{
		ASSERT(low <= high);
		m_VelRange[0] = low;
		m_VelRange[1] = high;
	}
	void FireWork::SetVelocityRange(const float* range)
	{
		ASSERT(range[0]<= range[1]);
		m_VelRange[0] = range[0];
		m_VelRange[1] = range[1];
	}
	void FireWork::SetTimeRange(float low, float high)
	{
		ASSERT(low<=high);
		m_TimeRange[0] = low;
		m_TimeRange[1] = high;
	}
	void FireWork::SetTimeRange(const float* range)
	{
		ASSERT(range[0]<=range[1]);
		m_TimeRange[0] = range[0];
		m_TimeRange[1] = range[1];
	}
	void FireWork::SetAcceleration(const float* acc)
	{
		m_Acc[0] = acc[0];
		m_Acc[1] = acc[1];
		m_Acc[2] = acc[2];
	}
	void FireWork::SetDistribution(Distribution dtb)
	{
		m_Distribution = dtb;
	}
	void FireWork::SetParticleCount(unsigned int count)
	{
		m_Count = count;
	}
	void FireWork::RenderImGui()
	{
		if(ImGui::Button("Firework Reset", ImVec2(50.f, 25.0f)))
			Reset();
		ImGui::ColorEdit4("Firework Color", &(m_Color[0].r));
	}
}
