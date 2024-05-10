#include "pch.h"
#include "DemoSceneA.h"

namespace ptt
{
	void DemoSceneA::Init()
	{
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite(), "Quad Mesh");
		m_RootObj->PushChild(m_SelectedObj);

		m_SelectedObj = new SceneObj(nullptr, new Hanabi(300), "Hanabi");
		m_RootObj->PushChild(m_SelectedObj);
	}
	DemoSceneA::DemoSceneA(bool init)
	{
		m_RootObj = std::make_unique<SceneObj>(nullptr, nullptr, "Root Obj");
		if (init)
			Init();
	}
	DemoSceneA::~DemoSceneA()
	{
	}
	void DemoSceneA::Render()
	{
	}
	void DemoSceneA::RenderImGui()
	{
	}
	void DemoSceneA::Update(float deltaTime)
	{
	}
}