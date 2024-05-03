#pragma once
namespace ptt
{
	class ImGuiContext
	{
	private:
		bool m_Init;

		static ImGuiContext* s_Instance;

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

	};
}