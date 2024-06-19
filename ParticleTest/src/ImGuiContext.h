#pragma once
#include "ImGuiWindows/StyleEditor.h"
#include "ImGuiWindows/DialogManager.h"
#include "ImGuiWindows/TextureLoadDialog.h"
namespace ptt
{
	class ImGuiContext
	{
	private:
		bool m_Init;

		static ImGuiContext* s_Instance;

		std::unordered_map<std::string, ImGuiWindows*> m_ImGuiWindows;

		DialogManager m_DialogManager;

		void Terminate();
	public:
		ImGuiContext();
		~ImGuiContext();
		void Init(GLFWwindow* window);

		void ImGuiBegin();
		void ImGuiEnd();

		void Popup(const std::string& name);
		void UpdateDialogID();
		void ShowDialog(const std::string& name);
		ImGuiDialog* GetDialog(const std::string& name);

		static ImGuiContext* GetInstance();
		static void SaveStyle(const std::string& fileName);
		static void LoadStyle(const std::string& fileName);

		static void ShowWindow(const std::string& keyString);
		static void OpenWindow(const std::string& keyString);
		static void CloseWindow(const std::string& keyString);
	};
}