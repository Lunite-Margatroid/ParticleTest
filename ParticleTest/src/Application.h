#pragma once
#include "ImGuiContext.h"
#include "GlfwContext.h"
#include "DemoScene.h"
namespace ptt
{
	class Application
	{
	protected:
		GLFWwindow* m_Window;

		std::unique_ptr<ImGuiContext> m_ImGuiCtx;
		std::unique_ptr<GlfwContext> m_GlfwCtx;

		std::unique_ptr<MenuScene> m_Menu;

		float m_LastTime;
		float m_CurrentTime;
		float m_DeltaTime;

		bool m_Run;

		void UpdateTime();

		virtual void Init();
	public:
		Application();
		virtual ~Application();

		virtual void Render();
		virtual void RenderImGui();
		virtual void Run();
	};
}