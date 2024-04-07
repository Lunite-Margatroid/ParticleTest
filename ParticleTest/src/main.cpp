#include "pch.h"
#include "Application.h"
#include "DemoScene.h"
class MyApp :public ptt::Application
{
public:
	MyApp()
	{
		m_Menu->RegistDemoScene<ptt::DemoScene>("Nothing Scene");
	}
	~MyApp() {}
};

int main()
{
	auto* app = new MyApp();
	app->Run();
	delete app;
	return 0;
}