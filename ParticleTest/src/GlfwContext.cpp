#include "pch.h"
#include "GlfwContext.h"
#include "Application.h"
namespace ptt
{

	GlfwContext::~GlfwContext()
	{
		Terminate();
	}

	GLFWwindow* GlfwContext::GetGlfwWindow()
	{
		return m_Window;
	}

	int GlfwContext::GetHeight() const
	{
		return m_Height;
	}

	int GlfwContext::GetWidth() const
	{
		return m_Width;
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

		// ��Ļ����ָ�� ����ȫ��ģʽ
		GLFWmonitor* primary = NULL;
		if(Application::IsFullScreen())
			primary = glfwGetPrimaryMonitor();

		GLFWwindow* window = glfwCreateWindow(m_Width, m_Height, title.c_str(), primary, NULL);
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

		InitInput();
	}

	void GlfwContext::InitInput()
	{
		Input::SetWindow(m_Window);
	}

	void GlfwContext::Terminate()
	{
		Input::FreeInstance();
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	GlfwContext::GlfwContext():m_Window(NULL), m_Height(0),m_Width(0),m_Init(false)
	{

	}
}