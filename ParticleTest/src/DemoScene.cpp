#include "pch.h"
#include "DemoScene.h"

namespace ptt
{
	DemoScene::DemoScene()
	{
	}
	DemoScene::~DemoScene()
	{
	}
	bool DemoScene::ShouleClose()
	{
		return false;
	}
	void DemoScene::Update(float deltaTime)
	{
	}
	void DemoScene::Render()
	{
	}
	void DemoScene::RenderImGui()
	{
		static char buffer[64];
		ImGui::InputText("Nothing Scene", buffer, 64);
	}
	MenuScene::MenuScene()
	{
		m_CurrentScene = nullptr;
	}
	MenuScene::~MenuScene()
	{
		if (m_CurrentScene)
			delete m_CurrentScene;
	}
	void MenuScene::RenderImGui()
	{
		static char sceneTitle[128];
		if (m_CurrentScene == nullptr)
		{
			ImGui::Begin("Menu");
			for (auto& item : m_Menu)
			{
				if (ImGui::Button(item.second.c_str()))
				{
					m_CurrentScene = item.first();
					strcpy(sceneTitle, item.second.c_str());
				}
			}
			ImGui::End();
		}
		else
		{
			ImGui::Begin(sceneTitle);
			if (ImGui::Button("<- back to mune"))
			{
				delete m_CurrentScene;
				m_CurrentScene = nullptr;
			}
			else
			{
				m_CurrentScene->RenderImGui();
			}
			ImGui::End();
		}
	}
	void MenuScene::Render()
	{
		if (m_CurrentScene)
			m_CurrentScene->Render();
	}
}