#include "pch.h"
#include "FireworkScene.h"

namespace ptt
{
	FireworkScene::FireworkScene()
	{
		m_FW = new SceneObj(nullptr, new FireWork());
		m_RootObj->PushChild(m_FW);
		m_FW->SetPosition(glm::vec3(0.0f, 0.f, -5.0f));
		//m_FireWork = nullptr;

		SceneObj* fw = new SceneObj(nullptr, new FireWork());
		m_RootObj->PushChild(fw);
		fw->SetPosition(glm::vec3(0.0f, 0.f, -5.0f));

		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}
	FireworkScene::~FireworkScene()
	{
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}
	void FireworkScene::Render()
	{
		SpriteTest::Render();
	}
	void FireworkScene::RenderImGui()
	{
		SpriteTest::RenderImGui();
		if (m_FW)
		{
			ImGuiInterface* gui = dynamic_cast<ImGuiInterface*>(m_FW->GetSprite());
			if (gui)
				gui->RenderImGui();
		}
	}
	void FireworkScene::Update(float deltaTime)
	{
		SpriteTest::Update(deltaTime);
	}
}