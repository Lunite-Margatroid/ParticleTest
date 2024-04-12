#include "pch.h"
#include "SceneFireLoop.h"

namespace ptt
{
	SceneFirLoop::SceneFirLoop() :
		m_Shader("", ""),
		m_Particle(m_Shader.GetShaderID()),
		m_ParticlePos(0.0f, 0.0f, 5.0f),
		m_AngVel(PI),
		m_Axis(0.0f, 1.0f, 0.0f),
		m_Radius(5.0f),
		m_Angle(0.0f),
		m_DeltaTime(0.0f)
	{
	}
	SceneFirLoop::~SceneFirLoop()
	{
	}
	void SceneFirLoop::SetUniform()
	{
		static glm::mat4 modelTrans;
		static glm::mat4 viewTrans;
		static glm::mat4 projectionTrans;
		static glm::mat4 mvpTrans;
		modelTrans = glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0.0f, 1.0f, 0.0f));
		modelTrans = glm::translate(modelTrans, glm::vec3(1.0f, 0.0f, 0.0f));
		
		viewTrans = m_Camera.GetViewTrans();
		projectionTrans = m_Camera.GetProjectionTrans();
		mvpTrans = projectionTrans * viewTrans * modelTrans;

		m_Shader.SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader.SetUniform1f("u_DeltaTime", m_DeltaTime);
	}
	void SceneFirLoop::Render()
	{
		m_Particle.Draw();
	}
	void SceneFirLoop::RenderImGui()
	{
		ImGui::SliderFloat("Angular Velocity", &m_AngVel, 0.0f, PI * 4);
		ImGui::DragFloat("Radius", &m_Radius, 1.0f, 1.0f, 40.0f);
	}
	void SceneFirLoop::Update(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}
}