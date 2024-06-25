#include "pch.h"
#include "Application.h"
#include "SceneObj/illuminant.h"
#include "demoscene/DemoSceneModel.h"
#include "ImGuiWindows/AddObjectDialog.h"

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
		m_ImGuiCtx = std::make_unique<ImGuiContext>();

		m_GlfwCtx->Init(m_Width, m_Height);
		m_Window = m_GlfwCtx->GetGlfwWindow();
		m_ImGuiCtx->Init(m_Window);

		m_Renderer = Renderer::GetInstance();

		// ½Ø¶ÏImGuiÏûÏ¢
		glfwSetKeyCallback(m_Window, PreCallbackKey);

		m_SceneWindow.Init(m_SceneWidth, m_SceneHeight);

		
	}
	Application::Application()
		:m_DemosceneWindow("Demoscene"),
		m_SceneWindow("Scene"),
		m_SceneProperty("Scene Propterty", nullptr)
	{
		ASSERT(s_Instance == nullptr);
		s_Instance = this;
		m_Run = true;
		m_FullScreen = false;
		m_MultiSample = true;
		m_CurrentScene = nullptr;
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
		// render ui
		// glClear(GL_COLOR_BUFFER_BIT);
		RenderImGui();

		// swap default framebuffer
		glfwSwapBuffers(m_Window);
	}

	void Application::RenderImGui()
	{
		m_ImGuiCtx->ImGuiBegin();

		RenderMenuBar();

		if (m_DemosceneWindow.IsOpen())
			m_DemosceneWindow.ShowWindow();

		m_CurrentScene = m_DemosceneWindow.GetScene();
		m_SceneWindow.SetScene(m_CurrentScene);
		m_SceneProperty.SetScene(m_CurrentScene);

		if (m_SceneWindow.IsOpen())
			m_SceneWindow.ShowWindow();
		if (m_SceneProperty.IsOpen())
			m_SceneProperty.ShowWindow();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

			if (ImGui::BeginMenu("Winodw"))
			{
				ImGui::MenuItem("Demoscne Loader", NULL, m_DemosceneWindow.GetBoolPtr());
				ImGui::MenuItem("Scene Window", NULL, m_SceneWindow.GetBoolPtr());
				ImGui::MenuItem("Scene Proterty", NULL, m_SceneProperty.GetBoolPtr());
				
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::MenuItem("Load Model"))
				{
					IGFD::FileDialogConfig config;
					config.path = "L:/OpenGL/model";
					ImGuiFileDialog::Instance()->OpenDialog("Load Model", "Choose File", ".fbx,.blend,.pmx,.*", config);
				}
				ImGui::Separator();
				if(ImGui::BeginMenu("Add Scene Object"))
				{
					if (ImGui::MenuItem("Add Static Object"))
					{
						AddObjectDialog * dialog = dynamic_cast<AddObjectDialog*>(m_ImGuiCtx->GetDialog("Add Object"));
						DemoSceneModel* scene = dynamic_cast<DemoSceneModel*>(GetCurrentScene());
						if (dialog && scene)
						{
							dialog->InitWindow(scene);
							dialog->Popup();
						}
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Load Texture"))
				{
					m_ImGuiCtx->Popup("Texture Load");
				}

				if (ImGui::BeginMenu("Render"))
				{
					if (ImGui::MenuItem("Rendering Setting"))
					{
						m_ImGuiCtx->Popup("Rendering Setting");
					}
					ImGui::EndMenu();
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
		// ---------------- Load Model Dialog -------------------
		if (ImGuiFileDialog::Instance()->Display("Load Model")) {
			if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				// action

				DemoSceneModel* scene = dynamic_cast<DemoSceneModel*>(m_CurrentScene);
				if (scene)
				{
					scene->LoadModel(filePathName);
				}
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}

		// ----------------Style Editor------------------------
		m_ImGuiCtx->ShowWindow("Style Editor");

		// ----------------- Texture loader----------------------
		m_ImGuiCtx->ShowDialog("Texture Load");

		// ------------------ adding Object --------------
		m_ImGuiCtx->ShowDialog("Add Object");
		
		// ------------------ render setting -----------
		m_ImGuiCtx->ShowDialog("Rendering Setting");
	}

	Application* Application::GetInstance()
	{
		ASSERT(s_Instance);
		return s_Instance;
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
		return GetInstance()->m_CurrentScene;
	}
	void Application::SetCurrentScene(DemoScene* scene)
	{
		GetInstance()->m_CurrentScene = scene;
	}
	float Application::GetFPS()
	{
		return GetInstance()->m_FPS;
	}
	void Application::OpenDialog(const std::string& name)
	{
		GetInstance()->m_ImGuiCtx->Popup(name);
	}
	void Application::ShowDialog(const std::string& name)
	{
		GetInstance()->m_ImGuiCtx->ShowDialog(name);
	}
	ImGuiDialog* Application::GetDialog(const std::string& name)
	{
		return GetInstance()->m_ImGuiCtx->GetDialog(name);
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
		if (m_DeltaTime > 0.0f)
			m_FPS = 1.0f / m_DeltaTime;

		m_SceneWindow.Update(m_DeltaTime);
		m_SceneWindow.SetMultisample(m_MultiSample);
	}
}
