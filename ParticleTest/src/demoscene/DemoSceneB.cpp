#include "pch.h"
#include "DemoSceneB.h"

namespace ptt
{
	void DemoSceneB::Init()
	{
		ColoredSprite<1>* sprite;
		m_SelectedObj = m_RootObj.get();

		m_SelectedObj = new SceneObj(nullptr, dynamic_cast<Sprite*>(new CubeSprite()), "cube1");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
		m_SelectedObj->GetSprite()->SetTransparency(true);
		sprite = dynamic_cast<ColoredSprite<1>*>(m_SelectedObj->GetSprite());
		if(sprite)
			sprite->SetColor(glm::vec4(1.0f, 0.0f,0.0f, 0.7f),0);

		m_SelectedObj = new SceneObj(nullptr, dynamic_cast<Sprite*>(new CubeSprite()), "cube2");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
		m_SelectedObj->SetPosition(glm::vec3(2.0f, 2.0f, 2.0f));
		m_SelectedObj->GetSprite()->SetTransparency(true);
		sprite = dynamic_cast<ColoredSprite<1>*>(m_SelectedObj->GetSprite());
		if (sprite)
			sprite->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.7f), 0);


		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "cube3");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
		m_SelectedObj->SetPosition(glm::vec3(-1.0f, -1.0f,-1.0f));
		m_SelectedObj->GetSprite()->SetTransparency(true);
		sprite = dynamic_cast<ColoredSprite<1>*>(m_SelectedObj->GetSprite());
		if (sprite)
			sprite->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.7f), 0);

		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "cube4");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
		m_SelectedObj->SetPosition(glm::vec3(1.0f, -1.0f, -1.0f));
		m_SelectedObj->GetSprite()->SetTransparency(true);
		sprite = dynamic_cast<ColoredSprite<1>*>(m_SelectedObj->GetSprite());
		if (sprite)
			sprite->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.7f), 0);

		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "cube5");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
		m_SelectedObj->SetPosition(glm::vec3(-1.0f, -1.0f, 1.0f));
		m_SelectedObj->GetSprite()->SetTransparency(true);
		sprite = dynamic_cast<ColoredSprite<1>*>(m_SelectedObj->GetSprite());
		if (sprite)
			sprite->SetColor(glm::vec4(0.0f, 1.0f, 0.5f, 0.7f), 0);

		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "cube6");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
		m_SelectedObj->SetPosition(glm::vec3(1.0f, -1.0f, 1.0f));
		m_SelectedObj->GetSprite()->SetTransparency(true);
		sprite = dynamic_cast<ColoredSprite<1>*>(m_SelectedObj->GetSprite());
		if (sprite)
			sprite->SetColor(glm::vec4(0.3f, 0.7f, 0.9f, 0.7f), 0);

		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite(), "Quad Mesh");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetPosition(glm::vec3(0.0f, -5.0f, 0.0f));

		m_Camera = Renderer::GetCamera(Renderer::Cameras::Camera3D_Alpha);
		Renderer::SetCurrentCamera(m_Camera);

		Camera3D* camera = dynamic_cast<Camera3D*>(m_Camera);
		camera->SetPos(glm::vec3(0.0f, 0.f, 10.0f));

		Renderer::LoadTexture("./res/img/marisa.jpg");

	}
	DemoSceneB::DemoSceneB()
		:DemoSceneA(false)
	{
		Init();
	}
	DemoSceneB::~DemoSceneB()
	{
	}
	void DemoSceneB::Render()
	{
		DemoSceneA::Render();
	}
	void DemoSceneB::RenderImGui()
	{
		DemoSceneA::RenderImGui();
	}
	void DemoSceneB::Update(float deltaTime)
	{
		DemoSceneA::Update(deltaTime);
	}
}