#include "pch.h"
#include "Application.h"
#include "demoscene/DemoScene.h"
#include "demoscene/SinWave.h"
#include "demoscene/SceneFireLoop.h"
#include "demoscene/QuadMeshScene.h"
#include "demoscene/SpriteTest.h"
#include "demoscene/FireworkScene.h"
#include "demoscene/DemoSceneA.h"
#include "demoscene/DemoSceneB.h"
#include "Rand/Rand.h"
class MyApp :public ptt::Application
{
public:
	MyApp()
	{
		ptt::ImGuiContext::LoadStyle("./res/ImGuiStyle/PinkStyle.style");
		m_Menu->RegistDemoScene<ptt::DemoScene>("Nothing Scene");
		m_Menu->RegistDemoScene<ptt::SinWave>("Sin wave Scene");
		m_Menu->RegistDemoScene<ptt::SceneFireLoop>("Fire Loop Scene");
		m_Menu->RegistDemoScene<ptt::QuadMeshScene>("Quad Mesh Scene");
		m_Menu->RegistDemoScene<ptt::SpriteTest>("Quad Mest Sprite Scene");
		m_Menu->RegistDemoScene<ptt::FireworkScene>("Fire Work Scene");
		m_Menu->RegistDemoScene<ptt::DemoSceneA>("DemoSceneA");
		m_Menu->RegistDemoScene<ptt::DemoSceneB>("oit demoscene");
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