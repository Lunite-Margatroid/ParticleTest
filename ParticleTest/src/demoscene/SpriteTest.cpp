#include "pch.h"
#include "SpriteTest.h"

namespace ptt
{
	SpriteTest::SpriteTest():
		m_Color(1.0f, 1.0f, 1.f,1.f)
	{
		m_RootObj = std::make_unique<SceneObj>();
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite());
		m_RootObj->PushChild(m_SelectedObj);
		m_Shader = std::make_unique<LM::Shader>("./res/shader/QuadMeshSpriteVertex.shader", "./res/shader/QuadMeshSpriteFrag.shader");
		m_Camera = std::make_unique<Camera3D>();

		m_Yaw = m_SelectedObj->GetYaw();
		m_Pitch = m_SelectedObj->GetPitch();
		m_Roll = m_SelectedObj->GetRoll();

		m_Position = m_SelectedObj->GetPosition();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	SpriteTest::~SpriteTest()
	{
		glDisable(GL_BLEND);
	}
	void SpriteTest::Render()
	{
		Renderer::SetCurrentShader(m_Shader.get());
		Renderer::SetCurrentCamera(m_Camera.get());
		m_RootObj->Render();
	}
	void SpriteTest::RenderImGui()
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera)
		{
			const glm::vec3& cameraPos = camera->GetPosition();
			const glm::vec3& cameraAhead = camera->GetAhead();
			ImGui::Text("CameraPos: %.2f  %.2f  %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
			ImGui::Text("CameraAhead: %.2f  %.2f  %.2f", cameraAhead.x, cameraAhead.y, cameraAhead.z);
		}
		ImGui::SliderFloat3("Mesh Pos", &m_Position.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("Euler Angle", &m_Yaw, -PI, PI);
		ImGui::ColorEdit4("MeshColor", &m_Color.r);
	}
	void SpriteTest::Update(float deltaTime)
	{
		m_Camera->Update(deltaTime);
		m_RootObj->Update(deltaTime);

		m_SelectedObj->SetEulerAngle(&m_Yaw);
		m_SelectedObj->SetPosition(m_Position);

		QuadMeshSprite* sprite = dynamic_cast<QuadMeshSprite*>(m_SelectedObj->GetSprite());
		if (sprite)
		{
			sprite->SetMeshColor(m_Color);
		}
	}
}