#include "pch.h"
#include "GlfwContext.h"

namespace ptt
{
	GlfwContext* GlfwContext::s_Instance = nullptr;

	GlfwContext::~GlfwContext()
	{
		Terminate();
	}

	GlfwContext* GlfwContext::GetInstance()
	{
		if (s_Instance == nullptr)
			s_Instance = new GlfwContext();
		return s_Instance;
	}

	GLFWwindow* GlfwContext::GetGlfwWindow()
	{
		return GetInstance()->m_Window;
	}

	bool GlfwContext::Init(int width, int height, const std::string& title, int majorVersion, int minorVersion )
	{
		m_Width = width;
		m_Height = height;
		m_Init = true;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Fail to create a window" << std::endl;
			glfwTerminate();
			return false;
		}
		m_Window = window;

		// ����������
		glfwMakeContextCurrent(window);

		// ����opengl���� Ҫ������������֮��
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Fail to initialize glad" << std::endl;
			glfwTerminate();
			return false;
		}

		// ������ֱͬ��
		glfwSwapInterval(1);

		// �����ӿ�
		GLCall(glViewport(0, 0, m_Width, m_Height));
	}

	void GlfwContext::Terminate()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	GlfwContext::GlfwContext():m_Window(NULL), m_Height(0),m_Width(0),m_Init(false)
	{

	}
}