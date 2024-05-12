#pragma once
#include "ImGuiContext.h"
#include "GlfwContext.h"
#include "demoscene/DemoScene.h"
#include "Renderer/Renderer.h"
#include "glObj/FrameBuffer.h"
#include "glObj/FrameBufferMS.h"

namespace ptt
{
	class DemoScene;
	class MenuScene;

	class Application
	{
		static Application* s_Instance;
	protected:
		GLFWwindow* m_Window;

		std::unique_ptr<ImGuiContext> m_ImGuiCtx;
		std::unique_ptr<GlfwContext> m_GlfwCtx;
		std::unique_ptr<MenuScene> m_Menu;

		Renderer* m_Renderer;

		float m_LastTime;
		float m_CurrentTime;
		float m_DeltaTime;

		bool m_Run;
		bool m_FullScreen;
		bool m_MultiSample;
		int m_Width, m_Height;				// window's width and height
		int m_SceneWidth, m_SceneHeight;	// frame's width and height

		LM::FrameBuffer m_Framebuffer;
		LM::FrameBufferMS m_FramebufferMS;

		void UpdateTime();
		void Update();
		virtual void Init();
	public:
		Application();
		virtual ~Application();

		virtual void Render();
		virtual void RenderImGui();
		virtual void Run();

		static Application* GetInstance();
		static LM::FrameBuffer* GetFramebuffer();

		static bool IsFullScreen();

		static void PreCallbackKey(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void GetDefaultFrameBufferSize(int* width, int* height);
	};
}
