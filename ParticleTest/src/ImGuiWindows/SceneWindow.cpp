#include "pch.h"
#include "SceneWindow.h"
#include "Application.h"

namespace ptt
{
	void SceneWindow::Init(int width, int height)
	{
		m_SceneWidth = width;
		m_SceneHeight = height;
		m_Framebuffer.Init(m_SceneWidth, m_SceneHeight);
		m_FramebufferMS.Init(m_SceneWidth, m_SceneHeight, 4);
		m_Current = dynamic_cast<LM::FrameBuffer*>(&m_FramebufferMS);
	}
	SceneWindow::SceneWindow(const std::string& keyString, int width, int height)
		: ImGuiWindows(keyString), m_Scene(nullptr), m_SceneWidth(width), m_SceneHeight(height)
	{
		Init(width, height);
	}
	SceneWindow::SceneWindow(const std::string& keyString)
		:ImGuiWindows(keyString), m_Scene(nullptr)
	{
	}
	void SceneWindow::SetScene(DemoScene* scene)
	{
		m_Scene = scene;
	}
	const DemoScene* SceneWindow::GetScene() const
	{
		return m_Scene;
	}
	void SceneWindow::SetMultisample(bool multisample)
	{
		if (multisample)
			m_Current = dynamic_cast<LM::FrameBuffer*>(&m_Framebuffer);
		else
		{
			m_Current = dynamic_cast<LM::FrameBuffer*>(&m_FramebufferMS);
		}
	}
	bool SceneWindow::IsMultisample() const
	{
		return (void*)(m_Current )== (void*)(&m_FramebufferMS);
	}
	void SceneWindow::ShowWindow()
	{
		ImGui::Begin(m_keyString.c_str(), &m_Open);
		if (m_Scene == nullptr)
		{
			ImGui::End();
			return;
		}
		/*----------- render scene to framebuffer---------*/
		m_Current->Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glViewport(0, 0, m_Current->GetWidth(), m_Current->GetHeight());
		m_Scene->Render();
		if (IsMultisample())
		{
			dynamic_cast<LM::FrameBufferMS*>(m_Current)->BlitFrameBuffer(m_Framebuffer);
		}
		m_Current->Unbind();

		/*-------- render transparency obj ---------------*/
		// 关闭深度测试
		GLboolean depthEnable = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		// render
		m_Framebuffer.Bind();
		Renderer::GetOITContext()->Render();
		m_Framebuffer.Unbind();
		// 复原
		if (depthEnable)
			glEnable(GL_DEPTH_TEST);

		/*---------- render UI ------------------------------*/
		//glClear(GL_COLOR_BUFFER_BIT);

		ImVec2 windowPos = ImGui::GetCursorScreenPos();					// 当前窗口位置
		LM::FrameBuffer* framebuffer = &m_Framebuffer;	// 帧缓冲
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
			ImVec2(windowPos.x + drawWidth, windowPos.y + drawHeight),
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
					camera->RotateYaw(-sDeltaPos.x / 500.0f);
					camera->RotatePitch(-sDeltaPos.y / 500.0f);
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
	void SceneWindow::Update(float deltaTime)
	{
		if(m_Scene)
			m_Scene->Update(deltaTime);
	}
	LM::FrameBuffer* SceneWindow::GetFrameBuffer()
	{
		return &m_Framebuffer;
	}
	LM::FrameBufferMS* SceneWindow::GetFrameBufferMS()
	{
		return &m_FramebufferMS;
	}
}