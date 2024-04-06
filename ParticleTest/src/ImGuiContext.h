#pragma once
namespace ptt
{
	class ImGuiContext
	{
	private:
		bool m_Init;

		void Terminate();
	public:
		ImGuiContext();
		~ImGuiContext();
		void Init(GLFWwindow* window);

		void ImGuiBegin();
		void ImGuiEnd();
	};
}