#pragma once
#include "Input.h"

namespace ptt
{
	class GlfwContext
	{
	private:
		GLFWwindow* m_Window;

		int m_Height;
		int m_Width;
		bool m_Init;

		
		void Terminate();

	public:
		GlfwContext();
		~GlfwContext();
		bool Init(int width = 1600, int height = 900, const std::string& title = "Particle Test",
			int majorVersion = 4, int minorVersion = 5);
		void InitInput();
		GLFWwindow* GetGlfwWindow();

		int GetHeight()const;
		int GetWidth()const;
	};
}