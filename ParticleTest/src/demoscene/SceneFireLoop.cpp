#include "pch.h"
#include "SceneFireLoop.h"

namespace ptt
{
	void SceneFireLoop::Init()
	{
		m_Particle.InitShaderUniform();
		GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
	}
	SceneFireLoop::SceneFireLoop() :
		m_Shader("./res/shader/FireLoopVertex.shader", "./res/shader/FireLoopFrag.shader"),
		m_Particle(&m_Shader),
		m_ParticlePos(0.0f, 0.0f, 5.0f),
		m_AngVel(PI),
		m_Axis(0.0f, 1.0f, 0.0f),
		m_Radius(5.0f),
		m_Angle(0.0f),
		m_ParticleColor(1.0f,1.0f ,1.0f),
		m_VertexSize(1.0f)
	{
		m_Shader.Bind();
		m_Shader.SetUniform1f("u_DeltaTime", 0.0f);
		Init();
	}
	SceneFireLoop::~SceneFireLoop()
	{
		GLCall(glDisable(GL_PROGRAM_POINT_SIZE));
	}
	void SceneFireLoop::SetUniform()
	{
		static glm::mat4 modelTrans;
		static glm::mat4 viewTrans;
		static glm::mat4 projectionTrans;
		static glm::mat4 mvpTrans;
		modelTrans = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		modelTrans = glm::translate(modelTrans, glm::vec3(0.0f, 0.0f, 0.0f));
		viewTrans = m_Camera.GetViewTrans();
		projectionTrans = m_Camera.GetProjectionTrans();
		mvpTrans = projectionTrans * viewTrans * modelTrans;

		m_Shader.SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader.SetUniform3f("u_Position", m_ParticlePos.x, m_ParticlePos.y, m_ParticlePos.z);

		m_Shader.SetUniform1f("u_VertexSize", m_VertexSize);
		m_Shader.SetUniform3f("u_VertexColor", m_ParticleColor.r, m_ParticleColor.g, m_ParticleColor.b);
	}
	void SceneFireLoop::Render()
	{
		SetUniform();
		m_Particle.Draw();
	}
	void SceneFireLoop::RenderImGui()
	{
		const glm::vec3& cameraPos = m_Camera.GetPosition();
		const glm::vec3& cameraAhead = m_Camera.GetAhead();
		ImGui::SliderFloat("Angular Velocity", &m_AngVel, 0.0f, PI * 4);
		ImGui::SliderFloat("Radius", &m_Radius, 1.0f, 40.0f);

		ImGui::ColorPicker3("Particle Color", &m_ParticleColor.r);
		ImGui::SliderFloat("Vertex Size", &m_VertexSize, 1.0f, 100.0f);

		ImGui::Text("CameraPos: %.2f  %.2f  %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
		ImGui::Text("CameraAhead: %.2f  %.2f  %.2f", cameraAhead.x, cameraAhead.y, cameraAhead.z);
	}
	void SceneFireLoop::Update(float deltaTime)
	{
		m_Angle += m_AngVel * deltaTime;
		m_ParticlePos.x = cos(m_Angle) * m_Radius;
		m_ParticlePos.z = sin(m_Angle) * m_Radius;

		m_Particle.Update(deltaTime);
		m_Camera.Update(deltaTime);
	}
}