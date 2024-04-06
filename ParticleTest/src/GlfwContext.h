#pragma once

namespace ptt
{
	class GlfwContext
	{
	private:
		static GlfwContext* s_Instance;
		GLFWwindow* m_Window;

		int m_Height;
		int m_Width;
		bool m_Init;

		bool Init(int width = 1600, int height = 900, const std::string& title = "Particle Test", 
			int majorVersion = 4, int minorVersion = 6);
		void Terminate();

		GlfwContext();
		
	public:
		~GlfwContext();
		static GlfwContext* GetInstance();
		static GLFWwindow* GetGlfwWindow();
	};
}