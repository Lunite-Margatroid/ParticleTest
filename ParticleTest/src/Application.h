#pragma once
#include "ImGuiContext.h"
#include "GlfwContext.h"
#include "demoscene/DemoScene.h"
#include "Renderer/Renderer.h"
#include "glObj/FrameBuffer.h"
#include "glObj/FrameBufferMS.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "ImGuiWindows/DemosceneLoader.h"
#include "ImGuiWindows/SceneWindow.h"
#include "ImGuiWindows/SceneProperty.h"
#include "demoscene/DemoSceneModel.h"
#include "ImGuiWindows/TextureLoadDialog.h"
#include "ImGuiWindows/DialogManager.h"

namespace ptt
{
	class Application
	{
		static Application* s_Instance;
	protected:
		GLFWwindow* m_Window;

		std::unique_ptr<ImGuiContext> m_ImGuiCtx;
		std::unique_ptr<GlfwContext> m_GlfwCtx;

		Renderer* m_Renderer;

		float m_LastTime;
		float m_CurrentTime;
		float m_DeltaTime;

		bool m_Run;
		bool m_FullScreen;
		bool m_MultiSample;
		int m_Width, m_Height;				// window's width and height
		int m_SceneWidth, m_SceneHeight;	// frame's width and height

		float m_FPS;

		// windows
		DemosceneLoader m_DemosceneWindow;
		SceneWindow m_SceneWindow;
		SceneProperty m_SceneProperty;

		DemoScene* m_CurrentScene;

		void UpdateTime();
		void Update();
		virtual void Init();
	public:
		LM::FrameBuffer* m_Current;

		Application();
		virtual ~Application();

		virtual void Render();
		virtual void RenderImGui();
		virtual void Run();

		virtual void RenderMenuBar();


		static Application* GetInstance();

		static bool IsFullScreen();

		static void PreCallbackKey(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void GetDefaultFrameBufferSize(int* width, int* height);
		static std::pair<int, int> GetSceneFramebufferSize();

		static DemoScene* GetCurrentScene();
		static void SetCurrentScene(DemoScene* scene);
		static float GetFPS();

		static void OpenDialog(const std::string& name);
		static void ShowDialog(const std::string& name);

		static ImGuiDialog* GetDialog(const std::string& name);
	};
}
