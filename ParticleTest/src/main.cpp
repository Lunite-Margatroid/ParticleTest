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
#include "demoscene/LightedDemoScene.h"
#include "Rand/Rand.h"
class MyApp :public ptt::Application
{
public:
	MyApp()
	{
		ptt::ImGuiContext::LoadStyle("./res/ImGuiStyle/DarkPink.style");

		m_DemosceneWindow.RegistDemoScene<ptt::DemoScene>("Nothing Scene");
		m_DemosceneWindow.RegistDemoScene<ptt::SinWave>("Sin wave Scene");
		m_DemosceneWindow.RegistDemoScene<ptt::SceneFireLoop>("Fire Loop Scene");
		m_DemosceneWindow.RegistDemoScene<ptt::QuadMeshScene>("Quad Mesh Scene");
		m_DemosceneWindow.RegistDemoScene<ptt::SpriteTest>("Quad Mest Sprite Scene");
		m_DemosceneWindow.RegistDemoScene<ptt::FireworkScene>("Fire Work Scene");
		m_DemosceneWindow.RegistDemoScene<ptt::DemoSceneA>("DemoSceneA");
		m_DemosceneWindow.RegistDemoScene<ptt::DemoSceneB>("oit demoscene");
		m_DemosceneWindow.RegistDemoScene<ptt::LightedDemoScene>("Lighted DemoScene");

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