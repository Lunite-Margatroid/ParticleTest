#pragma once
#include "DemoScene.h"
#include "Particle.h"
#include "Shader.h"
#include "Camera3D.h"
namespace ptt
{
	class SceneFireLoop :public DemoScene
	{
	private:
		LM::Shader m_Shader;
		Particle m_Particle;

		glm::vec3 m_ParticlePos;
		Camera3D  m_Camera;

		glm::vec3 m_Axis;
		float m_Radius;
		float m_AngVel;
		float m_Angle;

		float m_VertexSize;
		glm::vec3 m_ParticleColor;

		void Init();

	public:
		SceneFireLoop();
		~SceneFireLoop();

		void SetUniform();
		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}