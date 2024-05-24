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

		// �ض�ImGui��Ϣ
		glfwSetKeyCallback(m_Window, PreCallbackKey);
	}
	Application::Application()
	{
		ASSERT(s_Instance == nullptr);
		s_Instance = this;
		m_Run = true;
		m_FullScreen = false;
		m_MultiSample = true;
		m_FPS = 0.0f;
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

		// �ر���Ȳ���
		GLboolean depthEnable = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		// render
		m_Framebuffer.Bind();
		Renderer::GetOITContext()->Render();
		m_Framebuffer.Unbind();
		// ��ԭ
		if (depthEnable)
			glEnable(GL_DEPTH_TEST);
		
		// render ui
		glClear(GL_COLOR_BUFFER_BIT);
		RenderImGui();

		// swap default framebuffer
		glfwSwapBuffers(m_Window);
	}

	void Application::RenderImGui()
	{
		m_ImGuiCtx->ImGuiBegin();

		RenderMenuBar();
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

	void Application::RenderMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
				}
				if (ImGui::MenuItem("New"))
				{
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Style Edit"))
				{
					m_ImGuiCtx->OpenWindow("Style Editor");
				}
				if (ImGui::MenuItem("Load Style"))
				{
					IGFD::FileDialogConfig config;
					config.path = "./res/ImGuiStyle";
					ImGuiFileDialog::Instance()->OpenDialog("Load Style", "Choose File", ".style", config);
				}
				if (ImGui::MenuItem("Save Style"))
				{
					IGFD::FileDialogConfig config;
					config.path = "./res/ImGuiStyle";
					ImGuiFileDialog::Instance()->OpenDialog("Save Style", "Choose File", ".style", config);
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}


		// ---------------- Load Style Dialog -------------------
		if (ImGuiFileDialog::Instance()->Display("Load Style")) {
			if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				// action
				m_ImGuiCtx->LoadStyle(filePathName);
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}


		// ---------------- Save Style Dialog -------------------
		if (ImGuiFileDialog::Instance()->Display("Save Style")) {
			if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				// action
				m_ImGuiCtx->SaveStyle(filePathName);
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}
		// ----------------Style Editor------------------------
		m_ImGuiCtx->ShowWindow("Style Editor");
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
	LM::FrameBuffer* Application::GetCurrentFramebuffer()
	{
		Application* app = GetInstance();
		if (app->m_MultiSample)
			return &(app->m_FramebufferMS);
		return &(app->m_Framebuffer);
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
	std::pair<int, int> Application::GetSceneFramebufferSize()
	{
		Application* app = GetInstance();
		return std::pair<int, int>(app->m_SceneWidth, app->m_SceneHeight);
	}
	DemoScene* Application::GetCurrentScene()
	{
		return GetInstance()->m_Menu->GetCurrentScene();
	}
	float Application::GetFPS()
	{
		return GetInstance() -> m_FPS;
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
		if (m_DeltaTime > 0.0f)
			m_FPS = 1.0f / m_DeltaTime;
	}
}
