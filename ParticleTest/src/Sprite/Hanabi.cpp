#include "pch.h"
#include "Hanabi.h"

namespace ptt
{
    void Hanabi::Init()
    {
        // 烟花
        // pos 3 float
        // time 1 float
        // vel 3 float
        size_t hanabiSize = sizeof(float) * 8 * m_Count;
        float* buffer = reinterpret_cast<float*>(new char[hanabiSize]);
		memset(buffer, 0, hanabiSize);
        GenData(buffer);

		m_Buffer[0].Init(hanabiSize, buffer, GL_DYNAMIC_COPY);
		m_Buffer[1].Init(hanabiSize, buffer, GL_DYNAMIC_COPY);

		m_VAO[0].SetVB(m_Buffer[0].GetID());
		m_VAO[0].SetMetaType(GL_POINTS);
		m_VAO[0].PushAttrib<float>(3);	// pos
		m_VAO[0].PushAttrib<float>(1);	// time
		m_VAO[0].PushAttrib<float>(3);	// vel
		m_VAO[0].PushAttrib<float>(1, LM::AttribLayout::skip_attrib);	// 占位
		m_VAO[0].ApplyLayout();

		m_VAO[1].SetVB(m_Buffer[1].GetID());
		m_VAO[1].SetMetaType(GL_POINTS);
		m_VAO[1].PushAttrib<float>(3);	// pos
		m_VAO[1].PushAttrib<float>(1);	// time
		m_VAO[1].PushAttrib<float>(3);	// vel
		m_VAO[1].PushAttrib<float>(1, LM::AttribLayout::skip_attrib);	// 占位
		m_VAO[1].ApplyLayout();

        delete[] buffer;

		// spark
		// pos 3 float
		// vel 3 float
		// time 1 float
		size_t sparkSize = sizeof(float) * 7 * m_Count * m_SparkCount;
		buffer = reinterpret_cast<float*>(new char[sparkSize]);
		memset(buffer, 0, sparkSize);
		m_vbSpark[0].Init(sparkSize, buffer, GL_DYNAMIC_COPY);
		m_vbSpark[1].Init(sparkSize, buffer, GL_DYNAMIC_COPY);

		m_vaoSpark[0].SetMetaType(GL_POINTS);
		m_vaoSpark[0].SetVB(m_vbSpark[0].GetID());
		m_vaoSpark[0].PushAttrib<float>(3);
		m_vaoSpark[0].PushAttrib<float>(3);
		m_vaoSpark[0].PushAttrib<float>(1);
		m_vaoSpark[0].ApplyLayout();

		m_vaoSpark[1].SetMetaType(GL_POINTS);
		m_vaoSpark[1].SetVB(m_vbSpark[1].GetID());
		m_vaoSpark[1].PushAttrib<float>(3);
		m_vaoSpark[1].PushAttrib<float>(3);
		m_vaoSpark[1].PushAttrib<float>(1);
		m_vaoSpark[1].ApplyLayout();
		delete[] buffer;

		LM::Shader* shader = Renderer::GetShader(LM::Shaders::HanabiSpark);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_Buffer[0].GetID());
		//shader->UniformBlockBinding("UnifVertexAtttib", 4);
		//glBindBufferBase(GL_UNIFORM_BUFFER, 4, m_Buffer[0].GetID());
    }
    void Hanabi::GenData(float* buffer)
    {
		float* vel = new float[m_Count];
		float* existTime = new float[m_Count];
		myrand::GenerateNormalDistribution<float>(vel, m_Count, m_VelHanabi[0], m_VelHanabi[1]);
		myrand::GenerateNormalDistribution<float>(existTime, m_Count, m_TimeHanabi[0], m_TimeHanabi[1]);
		
		
			for (unsigned int i = 0; i < m_Count; i++)
			{
				float* temp = buffer + (i * 8);
				if (m_Distribution == Distribution::random)
					myrand::GetRandUnitVec3(temp + 4);
				else
					myrand::GetUniformUnitSphere(temp + 4, i, m_Count);

				temp[4] *= vel[i];// velocity x
				temp[5] *= vel[i];// velocity y
				temp[6] *= vel[i];// velocity z
				temp[3] = existTime[i]; // time
			}

		delete[] vel;
		delete[] existTime;
    }
    Hanabi::Hanabi(unsigned int count, unsigned int sparkCount) :
        m_Count(count), m_SparkCount(sparkCount),
        m_kDF(0.1f), m_kSparkDF(0.4f),
        m_Acc(0.0f, -6.0f, 0.0f), m_SparkAcc(0.0f, -6.0f, 0.0f),
        m_Distribution(Distribution::uniform), m_sparkDistribution(Distribution::random),
        m_DeltaTime(0.0f),
		m_HanabiSize(10.0f),
		m_SparkSize(3.0f),
		m_BufferFlag(true)
    {
        m_VelHanabi[0] = 10.0f;
        m_VelHanabi[1] = 2.0f;
        m_VelSpark[0] = 0.5f;
        m_VelSpark[1] = 0.3f;
		m_TimeHanabi[0] = 2.0f;
		m_TimeHanabi[1] = 0.3f;
		m_TimeSpark[0] = 0.5f;
		m_TimeSpark[1] = 0.2f;
        m_Color[0] = glm::vec4(1.0f, 1.0f, 1.0f ,1.0f);
		m_Color[1] = glm::vec4(1.0f);
		m_ExistTime = m_TimeHanabi[0] + m_TimeSpark[0] + 2 * (m_TimeHanabi[1] + m_TimeSpark[1]);

		m_ShaderName = LM::Shaders::Hanabi;
		Init();
    }
    Hanabi::~Hanabi()
    {
    }

	void Hanabi::Update(float deltaTime)
	{
		m_DeltaTime = deltaTime;
		if (m_ExistTime > 0.0f)
			m_ExistTime -= deltaTime;
	}

	void Hanabi::Render(const glm::mat4& modelTrans)
	{
		if (m_ExistTime < 0.0f)
			return;

		// ------------- Render Hanabi ----------------
		tfbShader* shader = dynamic_cast<tfbShader*>(Renderer::GetShader(LM::Shaders::Hanabi));
		ASSERT(shader);
		Camera* camera = Renderer::GetCurrentCamera();
		ASSERT(camera);
		glm::mat4& mvTrans = Renderer::GetMVTrans();
		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		mvTrans = camera->GetViewTrans() * modelTrans;
		mvpTrans = camera->GetProjectionTrans() * mvTrans;

		shader->Bind();
		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));
		shader->SetUniform1f("u_DeltaTime", m_DeltaTime);
		shader->SetUniform3f("u_Accelerate", &m_Acc.x);
		shader->SetUniform4f("u_VertexColor", &m_Color[0].r);
		shader->SetUniform1f("u_VertexSize", m_HanabiSize);
		shader->SetUniform1f("u_kDF", m_kDF);
		shader->SetUniform1f("u_Far", camera->GetFar());

		static size_t size = m_Count * 8 * sizeof(float);
		if (m_BufferFlag)
		{
			shader->BindBufferRange(0, m_Buffer[0].GetID(), 0, size);
			shader->BeginTransformFeedback(GL_POINTS);
			m_VAO[1].DrawArray(m_Count);

		}
		else
		{
			shader->BindBufferRange(0, m_Buffer[1].GetID(), 0, size);
			shader->BeginTransformFeedback(GL_POINTS);
			m_VAO[0].DrawArray(m_Count);
		}
		shader->EndTransformFeedback();
		shader->UnbindTransformFeedback();
		

		// ------------------ Render Spark -------------------

		shader = dynamic_cast<tfbShader*>(Renderer::GetShader(LM::Shaders::HanabiSpark));
		ASSERT(shader);
		shader->Bind();
		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));
		shader->SetUniform1f("u_DeltaTime", m_DeltaTime);
		shader->SetUniform3f("u_Accelerate", &m_SparkAcc.x);
		shader->SetUniform1f("u_VertexSize", m_SparkSize);
		shader->SetUniform1f("u_kDF",m_kSparkDF);
		shader->SetUniform1f("u_Far", camera->GetFar());

		shader->SetUniform1f("u_AverageVel", m_VelSpark[0]);
		shader->SetUniform1f("u_VelSD", m_VelSpark[1]);

		shader->SetUniform1f("u_AverageTime",m_TimeSpark[0]);
		shader->SetUniform1f("u_TimeSD", m_TimeSpark[1]);

		shader->SetUniform1i("u_Count", m_Count);

		shader->SetUniform4f("u_VertexColor", &m_Color[1].r);

		size = sizeof(float) * m_Count * m_SparkCount * 7;
		if (m_BufferFlag)
		{
			shader->BindBufferRange(0, m_vbSpark[0].GetID(), 0, size);
			shader->BeginTransformFeedback(GL_POINTS);
			m_vaoSpark[1].DrawArray(m_Count * m_SparkCount);

		}
		else
		{
			shader->BindBufferRange(0, m_vbSpark[1].GetID(), 0, size);
			shader->BeginTransformFeedback(GL_POINTS);
			m_vaoSpark[0].DrawArray(m_Count * m_SparkCount);
		}
		shader->EndTransformFeedback();
		shader->UnbindTransformFeedback();
		// ------------------------------------------------------
		m_BufferFlag = !m_BufferFlag;
	}
	void Hanabi::Reset()
	{
		size_t hanabiSize = sizeof(float) * 8 * m_Count;
		float* buffer = reinterpret_cast<float*>(new char[hanabiSize]);
		memset(buffer, 0, hanabiSize);
		GenData(buffer);
		m_Buffer[0].SetData(0, hanabiSize, buffer);
		m_Buffer[1].SetData(0, hanabiSize, buffer);
		m_ExistTime = m_TimeHanabi[0] + m_TimeSpark[0] + 2 * (m_TimeHanabi[1] + m_TimeSpark[1]);
		delete[] buffer;
	}

	void Hanabi::RenderImGui()
	{
		ImGui::SeparatorText("Sprite - Firework");
		
		if (ImGui::Button("Firework Reset", ImVec2(200.f, 50.0f)))
			Reset();

		ImGui::BeginChild("Hanabi property", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY);
		ImGui::Text("Hanabi property");
		if(m_Distribution == Distribution::random)
			ImGui::Text("Current Direction Distribution: Random");
		else
			ImGui::Text("Current Direction Distribution: Uniform");
		if (ImGui::Button("Random Direction"))
		{
			m_Distribution = Distribution::random;
		}
		if (ImGui::Button("Uniform Direction"))
		{
			m_Distribution = Distribution::uniform;
		}
		//ImGui::DragFloat("Vertex Point Size", &m_VertexSize);
		ImGui::SliderFloat("Point Size", &m_HanabiSize, 1.0f, 50.0f);
		ImGui::SliderFloat("Gravity Acc", &m_Acc.y, -20.0f, 0.0f);
		ImGui::SliderFloat("k Drag Force", &m_kDF, 0.0f, 0.4f);
		ImGui::SliderFloat("Average Velocity", m_VelHanabi, 1.0f, 100.0f);
		ImGui::SliderFloat("standard deviation", m_VelHanabi + 1, 0.0f, 10.f);
		ImGui::SliderFloat("Existing Time", m_TimeHanabi, 0.0f, 10.0f);
		ImGui::SliderFloat("standard deciation", m_TimeHanabi + 1, 0.0f, 5.0f);
		ImGui::ColorEdit4("Firework Color", &(m_Color[0].r));
		ImGui::EndChild();

		ImGui::BeginChild("Spark property", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY);
		ImGui::Text("Spark property");
		ImGui::SliderFloat("Point Size", &m_SparkSize, 1.0f, 50.0f);
		ImGui::SliderFloat("Gravity Acc", &m_SparkAcc.y, -20.0f, 0.0f);
		ImGui::SliderFloat("k Drag Force", &m_kSparkDF, 0.0f, 0.6f);
		ImGui::SliderFloat("Average Velocity", m_VelSpark, 1.0f, 100.0f);
		ImGui::SliderFloat("standard deviation", m_VelSpark + 1, 0.0f, 10.f);
		ImGui::SliderFloat("Existing Time", m_TimeSpark, 0.0f, 10.0f);
		ImGui::SliderFloat("standard deciation", m_TimeSpark + 1, 0.0f, 5.0f);
		ImGui::ColorEdit4("Firework Color", &(m_Color[1].r));
		ImGui::EndChild();
	}
}