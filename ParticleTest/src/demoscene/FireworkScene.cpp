#include "pch.h"
#include "FireworkScene.h"

namespace ptt
{
	FireworkScene::FireworkScene()
	{
		SceneObj* obj = new SceneObj(nullptr, new FireWork());
		m_RootObj->PushChild(obj);
		obj->SetPosition(glm::vec3(0.0f,0.f,-5.0f));
	}
	FireworkScene::~FireworkScene()
	{
	}
	void FireworkScene::Render()
	{
		SpriteTest::Render();
	}
	void FireworkScene::RenderImGui()
	{
		SpriteTest::RenderImGui();
	}
	void FireworkScene::Update(float deltaTime)
	{
		SpriteTest::Update(deltaTime);
	}
}