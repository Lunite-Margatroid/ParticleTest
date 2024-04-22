#include "pch.h"
#include "Application.h"
#include "demoscene/DemoScene.h"
#include "demoscene/SinWave.h"
#include "demoscene/SceneFireLoop.h"
#include "demoscene/QuadMeshScene.h"
#include "demoscene/SpriteTest.h"
class MyApp :public ptt::Application
{
public:
	MyApp()
	{
		m_Menu->RegistDemoScene<ptt::DemoScene>("Nothing Scene");
		m_Menu->RegistDemoScene<ptt::SinWave>("Sin wave Scene");
		m_Menu->RegistDemoScene<ptt::SceneFireLoop>("Fire Loop Scene");
		m_Menu->RegistDemoScene<ptt::QuadMeshScene>("Quad Mesh Scene");
		m_Menu->RegistDemoScene<ptt::SpriteTest>("Quad Mest Sprite Scene");
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