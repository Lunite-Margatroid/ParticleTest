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
			ImVec2 windowPos = ImGui::GetCursorScreenPos();					// 当前窗口位置
			LM::FrameBuffer* framebuffer = Application::GetFramebuffer();	// 帧缓冲
			ImVec2& windowSize = ImGui::GetWindowSize();					// 窗口大小

			float drawWidth;
			float drawHeight;
			float aspectRation = framebuffer->GetAspectRatio();	// 长宽比
			drawWidth = windowSize.y * aspectRation;
			drawHeight = windowSize.x / aspectRation;

			if (windowSize.x / windowSize.y > aspectRation)
			{
				drawHeight = windowSize.y;
				windowPos.x += (windowSize.x - drawWidth) / 2;
			}
			else
			{
				drawWidth = windowSize.x;
				windowPos.y += (windowSize.y - drawHeight) / 2;
			}

			ImGui::GetWindowDrawList()->AddImage							// 绘制帧缓冲
			(
				(void*)framebuffer->GetTextureID(),
				windowPos,
				ImVec2(windowPos.x+ drawWidth, windowPos.y+ drawHeight),
				ImVec2(0, 1),
				ImVec2(1, 0)
			);

			//std::cout << "window pos: " << windowPos.x << ',' << windowPos.y << std::endl;

			ImVec2 mouseDrag = ImGui::GetMouseDragDelta();
			//std::cout << "Mouse Drag: " << "x = " << mouseDrag.x << " y = " << mouseDrag.y << std::endl;
			
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			static ImVec2 sLastCursor;
			static ImVec2 sDeltaPos;
			if (io.MouseDown[0])	// 左键按下
			{
				// 这里windowPos 是scene绘制区域的左上角
				if (io.MouseClickedPos[0].x >= windowPos.x &&
					io.MouseClickedPos[0].x <= windowPos.x + drawWidth &&
					io.MouseClickedPos[0].y >= windowPos.y &&
					io.MouseClickedPos[0].y <= windowPos.y + drawHeight)	// 左键点击位置在目标区域内
				{
					sDeltaPos.x = io.MousePos.x - sLastCursor.x;
					sDeltaPos.y = io.MousePos.y - sLastCursor.y;
					// std::cout << "Mouse Drag dleta Pos: " << sDeltaPos.x << ", " << sDeltaPos.y << std::endl;
					if (Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera()))
					{
						camera->RotateYaw(sDeltaPos.x / 500.0f);
						camera->RotatePitch(sDeltaPos.y / 500.0f);
					}
					
				}
			}
			sLastCursor = ImGui::GetMousePos();

			/*if(ImGui::IsMouseHoveringRect(windowPos, ImVec2(drawWidth + windowPos.x, drawHeight + windowPos.y)))
				std:: cout << "Cursor is hovering on Scene ViewPort.\n";
			else
				std::cout << "Cursor doesn't hovering on Scene ViewPort.\n";*/
			//ImGuiIO& io = ImGui::GetIO(); (void)io;
			/*static ImVec2 sLastCursor;
			sLastCursor = ImGui::GetMousePosOnOpeningCurrentPopup();
			std::cout << "MousePosOnOpeningCurrentPopup: ("<< sLastCursor.x << ',' << sLastCursor.y << ")\n";

			sLastCursor = ImGui::GetMousePos();
			std::cout << "MousePos: (" << sLastCursor.x << ',' << sLastCursor.y << ")\n";*/
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