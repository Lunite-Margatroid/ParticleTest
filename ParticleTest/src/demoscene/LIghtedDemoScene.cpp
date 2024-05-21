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
		:DemoSceneA(false),
		m_DirLightBuffer(0, nullptr, LM::LightType::DirectionLight),
		m_PointLightBuffer(0, nullptr, LM::LightType::PointLight),
		m_SpotLightBuffer(0, nullptr, LM::LightType::SpotLight)
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