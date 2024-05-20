#include "pch.h"
#include "LightedDemoScene.h"

namespace ptt
{
	void LightedDemoScene::Init()
	{
	}
	void LightedDemoScene::LightEditor()
	{
	}
	LightedDemoScene::LightedDemoScene()
		:DemoSceneA(false)
	{
		Init();
	}
	LightedDemoScene::~LightedDemoScene()
	{
	}
	void LightedDemoScene::RenderImGui()
	{
		LightEditor();
		DemoSceneA::RenderImGui();
	}
}