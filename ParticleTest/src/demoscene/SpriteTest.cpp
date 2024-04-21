#include "pch.h"
#include "SpriteTest.h"

namespace ptt
{
	SpriteTest::SpriteTest()
	{
		m_RootObj = std::make_unique<SceneObj>();
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite());
		m_RootObj->PushChild(m_SelectedObj);
		m_Shader = std::make_unique<LM::Shader>("./res/shader/QuadMeshVertex.shader", "./res/shader/QuadMeshFrag.shader");
		m_Camera = std::make_unique<Camera3D>();
	}
	SpriteTest::~SpriteTest()
	{
	}
	void SpriteTest::Render()
	{
		m_RootObj->Render();
	}
	void SpriteTest::RenderImGui()
	{
	}
	void SpriteTest::Update(float deltaTime)
	{
		m_RootObj->Update(deltaTime);
	}
	void QuadMeshSprite::Init()
	{
		const float tt = 1000.0f;
		float vertice[] =
		{
			// x      z
			-tt, -tt,
			-tt, tt,
			tt, tt,
			tt, -tt
		};

		m_Buffer.Init(sizeof(vertice), vertice, GL_STATIC_DRAW);
		m_VAO.SetVB(m_Buffer.GetID());
		m_VAO.PushAttrib<float>(2);
		m_VAO.ApplyLayout();
		m_VAO.SetMetaType(GL_TRIANGLE_FAN);
	}
	QuadMeshSprite::QuadMeshSprite()
	{
		Init();
	}
	QuadMeshSprite::~QuadMeshSprite()
	{
	}
	void QuadMeshSprite::Render(glm::mat4& modelTrans)
	{
	}
}