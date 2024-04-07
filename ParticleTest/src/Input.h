#pragma once
#define IMPL_INPUT
namespace ptt
{
	class Input
	{
	private:
		GLFWwindow* m_Window;
		static Input* s_Instance;
		static Input* GetInstance();
		Input();
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int mousecode);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static void SetWindow(GLFWwindow* window);
		static void FreeInstance();
	};
}

#define INPUT_GLFW_WINDOW_PTR GetInstance()->m_Window