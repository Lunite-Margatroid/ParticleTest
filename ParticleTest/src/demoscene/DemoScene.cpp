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
		{// render menu
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
			// render scene ui
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

			// render scene on ImGui window
			ImGui::Begin("Scene");
			ImVec2& windowPos = ImGui::GetCursorScreenPos();				// 当前窗口位置
			LM::FrameBuffer* framebuffer = Application::GetFramebuffer();	// 帧缓冲
			ImVec2& windowSize = ImGui::GetWindowSize();					// 窗口大小
			float drawWidth;
			float drawHeight;
			float aspectRation = framebuffer->GetAspectRatio();
			drawWidth = windowSize.y * aspectRation;
			drawHeight = windowSize.x / aspectRation;

			if (windowSize.x / windowSize.y > aspectRation)
			{
				drawHeight = windowSize.y;
			}
			else
			{
				drawWidth = windowSize.x;
			}

			ImGui::GetWindowDrawList()->AddImage							// 绘制帧缓冲
			(
				(void*)framebuffer->GetTextureID(),
				windowPos,
				ImVec2(windowPos.x+ drawWidth, windowPos.y+ drawHeight),
				ImVec2(0, 1),
				ImVec2(1, 0)
				);
			ImGui::End();
		}
	}
	void MenuScene::Render()
	{
		if (m_CurrentScene)
			m_CurrentScene->Render();
	}
	void MenuScene::Update(float deltaTime)
	{
		if(m_CurrentScene)
			m_CurrentScene->Update(deltaTime);
	}
}