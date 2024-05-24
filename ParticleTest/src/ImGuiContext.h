#pragma once
#include "ImGuiWindows/StyleEditor.h"
namespace ptt
{
	class ImGuiContext
	{
	private:
		bool m_Init;

		static ImGuiContext* s_Instance;

		std::unordered_map<std::string, ImGuiWindows*> m_ImGuiWindows;

		void Terminate();
	public:
		ImGuiContext();
		~ImGuiContext();
		void Init(GLFWwindow* window);

		void ImGuiBegin();
		void ImGuiEnd();

		static ImGuiContext* GetInstance();
		static void SaveStyle(const std::string& fileName);
		static void LoadStyle(const std::string& fileName);

		static void ShowWindow(const std::string& keyString);
		static void OpenWindow(const std::string& keyString);
		static void CloseWindow(const std::string& keyString);


	};
}