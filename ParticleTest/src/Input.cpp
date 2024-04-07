#include "pch.h"
#include "Input.h"

namespace ptt
{
	Input* Input::s_Instance = nullptr;

	Input* Input::GetInstance()
	{
		if(!s_Instance)
			return s_Instance = new Input;
		return s_Instance;
	}

	Input::Input()
	{
		m_Window = nullptr;
	}

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = INPUT_GLFW_WINDOW_PTR;
		ASSERT(window != NULL);
		int status = glfwGetKey(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int mousecode)
	{
		auto window = INPUT_GLFW_WINDOW_PTR;
		ASSERT(window != NULL);
		int status = glfwGetMouseButton(window, mousecode);
		return status == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		double xpos, ypos;
		auto window = INPUT_GLFW_WINDOW_PTR;
		ASSERT(window != NULL);
		glfwGetCursorPos(window, &xpos, &ypos);

		return std::pair<float, float>((float)xpos, (float)ypos);
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}
	void Input::SetWindow(GLFWwindow* window)
	{
		GetInstance()->m_Window = window;
	}
	void Input::FreeInstance()
	{
		if (s_Instance)
			delete s_Instance;
	}
}
