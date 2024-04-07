#include "pch.h"

#include "Application.h"

namespace ptt
{

	void Application::Init()
	{
		m_GlfwCtx = std::make_unique<GlfwContext>();
		m_ImGuiCtx= std::make_unique<ImGuiContext>();

		m_GlfwCtx->Init();
		m_Window = m_GlfwCtx->GetGlfwWindow();
		m_ImGuiCtx->Init(m_Window);

		m_Menu = std::make_unique<MenuScene>();
	}
	Application::Application()
	{
		m_Run = true;
		Init();
	}
	Application::~Application()
	{
	}
	void Application::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, m_GlfwCtx->GetWidth(), m_GlfwCtx->GetHeight());
		m_Menu->Render();

		RenderImGui();
		glfwSwapBuffers(m_Window);
	}

	void Application::RenderImGui()
	{
		m_ImGuiCtx->ImGuiBegin();

		m_Menu->RenderImGui();
		m_ImGuiCtx->ImGuiEnd();
	}

	void Application::Run()
	{
		while (m_Run)
		{
			m_Run = (glfwWindowShouldClose(m_Window) == 0);
			glfwPollEvents();
			Render();
		}
	}

	void Application::UpdateTime()
	{
		static bool first = true;
		if (first)
		{
			m_CurrentTime = glfwGetTime();
			m_LastTime = m_CurrentTime;
			m_DeltaTime = 0.0f;
			first = false;
			return;
		}
		m_CurrentTime = glfwGetTime();
		m_DeltaTime = m_CurrentTime - m_LastTime;
		m_LastTime = m_CurrentTime;
	}
}
