#include "pch.h"
#include "Application.h"

namespace ptt
{
	Application* Application::s_Instance = nullptr;

	void Application::Init()
	{
		m_Width = 1600;
		m_Height = 900;
		m_SceneWidth = 1920;
		m_SceneHeight = 1080;

		m_GlfwCtx = std::make_unique<GlfwContext>();
		m_ImGuiCtx= std::make_unique<ImGuiContext>();

		m_GlfwCtx->Init(m_Width, m_Height);
		m_Window = m_GlfwCtx->GetGlfwWindow();
		m_ImGuiCtx->Init(m_Window);


		m_Menu = std::make_unique<MenuScene>();
		m_Renderer = Renderer::GetInstance();
		
		m_Framebuffer.Init(m_SceneWidth, m_SceneHeight);
		m_FramebufferMS.Init(m_SceneWidth, m_SceneHeight, 4);

		// ½Ø¶ÏImGuiÏûÏ¢
		glfwSetKeyCallback(m_Window, PreCallbackKey);
	}
	Application::Application()
	{
		ASSERT(s_Instance == nullptr);
		s_Instance = this;
		m_Run = true;
		m_FullScreen = false;
		m_MultiSample = true;
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
		if (m_MultiSample)
		{
			// render scene to multisample framebuffer
			m_FramebufferMS.Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glViewport(0, 0, m_FramebufferMS.GetWidth(), m_FramebufferMS.GetHeight());
			m_Menu->Render();
			m_FramebufferMS.BlitFrameBuffer(m_Framebuffer);
			m_FramebufferMS.Unbind();
		}
		else
		{
			// render scene to framebuffer
			m_Framebuffer.Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glViewport(0, 0, m_Framebuffer.GetWidth(), m_Framebuffer.GetHeight());
			m_Menu->Render();
			m_Framebuffer.Unbind();
		}
		
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
			glFlush();
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
	bool Application::IsFullScreen()
	{
		return GetInstance()->m_FullScreen;
	}
	void Application::PreCallbackKey(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
		{
			Application* app = GetInstance();
			app->m_FullScreen = !(app->m_FullScreen);
			if (app->m_FullScreen)
			{
				GLFWmonitor* primary = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(primary);
				int width = 1920, height = 1080;
				if (mode)
				{
					width = mode->width;
					height = mode->height;
				}
				//glfwGetMonitorPhysicalSize(primary, &width, &height);
				glfwSetWindowMonitor(window, primary, 0, 0, width, height, GLFW_DONT_CARE);
			}
			else
			{
				glfwSetWindowMonitor(window, NULL, 100, 100, app->m_Width, app->m_Height, GLFW_DONT_CARE);
			}
		}

		if (key == GLFW_KEY_M && action == GLFW_PRESS)
		{
			Application* app = GetInstance();
			app->m_MultiSample = !(app->m_MultiSample);
			std::cout << "Mulisample " << (app->m_MultiSample ? "On.\n" : "Off.\n");
		}
		ImGui_ImplGlfw_KeyCallback(window, key, scanCode, action, mods);
	}
	void Application::GetDefaultFrameBufferSize(int* width, int* height)
	{
		Application* app = GetInstance();
		glfwGetWindowSize(app->m_Window, width, height);
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
