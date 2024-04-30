#include "pch.h"
#include "FireworkScene.h"

namespace ptt
{
	FireworkScene::FireworkScene()
	{
		FireWork* hanabi = new FireWork(300, FireWork::Distribution::random);
		hanabi->SetTimeRange(2.0f, 2.5f);
		hanabi->Reset();
		m_FW = new SceneObj(nullptr, hanabi);
		m_RootObj->PushChild(m_FW);
		m_FW->SetPosition(glm::vec3(0.0f, 50.f, -50.0f));
		//m_FireWork = nullptr;

		/*SceneObj* fw = new SceneObj(nullptr, new FireWork(300,FireWork::Distribution::random));
		m_RootObj->PushChild(fw);
		fw->SetPosition(glm::vec3(0.0f, 5.f, -5.0f));*/

		m_Camera->SetPos(glm::vec3(0.0f, 1.f,0.0f));
		m_Camera->SetEulerAngle(PI / 4,  0.0f, 0.0f);

		GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
		GLCall(glEnable(GL_DEPTH_TEST));
	}
	FireworkScene::~FireworkScene()
	{
		GLCall(glDisable(GL_PROGRAM_POINT_SIZE));
		GLCall(glDisable(GL_DEPTH_TEST));
	}
	void FireworkScene::Render()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
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