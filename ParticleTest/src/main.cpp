#include "pch.h"
#include "Application.h"
#include "DemoScene.h"
#include "SinWave.h"
#include "SceneFireLoop.h"
class MyApp :public ptt::Application
{
public:
	MyApp()
	{
		m_Menu->RegistDemoScene<ptt::DemoScene>("Nothing Scene");
		m_Menu->RegistDemoScene<ptt::SinWave>("Sin wave Scene");
		m_Menu->RegistDemoScene<ptt::SceneFireLoop>("Fire Loop Scene");
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