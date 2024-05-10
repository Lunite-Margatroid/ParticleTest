#include "pch.h"
#include "Application.h"

namespace ptt
{
	Application* Application::s_Instance = nullptr;

	void Application::Init()
	{
		m_GlfwCtx = std::make_unique<GlfwContext>();
		m_ImGuiCtx= std::make_unique<ImGuiContext>();

		m_GlfwCtx->Init();
		m_Window = m_GlfwCtx->GetGlfwWindow();
		m_ImGuiCtx->Init(m_Window);

		m_Menu = std::make_unique<MenuScene>();
		m_Renderer = Renderer::GetInstance();

		m_Framebuffer.Init(1600, 900);
	}
	Application::Application()
	{
		ASSERT(s_Instance == nullptr);
		s_Instance = this;
		m_Run = true;
		Init();
	}
	Application::~Application()
	{
		delete m_Renderer;
		s_Instance = nullptr;
		//delete m_Menu;
	}
	void Application::Render()
	{
		// render scene to framebuffer
		m_Framebuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		// glViewport(0, 0, m_GlfwCtx->GetWidth(), m_GlfwCtx->GetHeight());
		glViewport(0, 0, m_Framebuffer.GetWidth(), m_Framebuffer.GetHeight());
		m_Menu->Render();
		m_Framebuffer.Unbind();

		// render ui
		glClear(GL_COLOR_BUFFER_BIT);
		RenderImGui();

		// swap default framebuffer
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
			Update();
			glfwPollEvents();
			Render();
		}
	}

	Application* Application::GetInstance()
	{
		ASSERT(s_Instance);
		return s_Instance;
	}

	LM::FrameBuffer* Application::GetFramebuffer()
	{
		Application* instance = GetInstance();
		ASSERT(instance);
		return &(instance->m_Framebuffer);
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
	void Application::Update()
	{
		UpdateTime();
		m_Menu->Update(m_DeltaTime);
	}
}
