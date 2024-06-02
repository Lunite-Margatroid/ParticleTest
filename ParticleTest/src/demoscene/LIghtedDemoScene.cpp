#include "pch.h"
#include "LightedDemoScene.h"

namespace ptt
{
	void LightedDemoScene::Init()
	{
		m_SelectedObj = m_RootObj.get();
		// �󶨹��ջ���
		m_DirLightBuffer.BindToShaderStorage(Renderer::GetShader(Renderer::Shaders::LightedMesh_P_N_T_TG), "DirLights");
		m_PointLightBuffer.BindToShaderStorage(Renderer::GetShader(Renderer::Shaders::LightedMesh_P_N_T_TG), "PointLights");
		m_SpotLightBuffer.BindToShaderStorage(Renderer::GetShader(Renderer::Shaders::LightedMesh_P_N_T_TG), "SpotLights");
		// ���
		m_Camera = Renderer::GetCamera(Renderer::Cameras::Camera3D_Alpha);
		Renderer::SetCurrentCamera(m_Camera);
		Camera3D* camera = dynamic_cast<Camera3D*>(m_Camera);
		if (camera)
			camera->SetPos(glm::vec3(0.0f, 4.0f, 10.0f));
		// �ذ�
		SceneObj* obj;
		Material* material;
		 obj = new SceneObj(m_RootObj.get(), dynamic_cast<Sprite*>(new QuadSprite()), "floor");
		obj->SetScale(glm::vec3(50.0f, 1.0f, 50.0f));
		material  = dynamic_cast<Material*>(obj->GetSprite());
		if (material)
		{
			material->SetTextureScale(LM::texture_diffuse, 0.02f, 0.02f);
			LM::Texture* tex = Renderer::LoadTexture("./res/img/floor2.jpg", LM::texture_diffuse);
			material->SetTexture(LM::texture_diffuse, tex);
		}
		obj = new SceneObj(m_RootObj.get(), dynamic_cast<Sprite*>(new CubeSprite()), "cube");
		obj->SetPosition(glm::vec3(10.f, 1.f, -3.f));
		// cube
		obj = new SceneObj(m_RootObj.get(), dynamic_cast<Sprite*>(new CubeSprite()), "cube1");
		obj->SetPosition(glm::vec3(1.5f, 1.4f, 6.4f));
		material = dynamic_cast<Material*>(obj->GetSprite());
		if (material)
		{
			LM::Texture* tex = Renderer::LoadTexture("./res/img/container2.png", LM::texture_diffuse);
			material->SetTexture(LM::texture_diffuse, tex);
			tex = Renderer::LoadTexture("./res/img/container2_specular.png", LM::texture_specular);
			material->SetTexture(LM::texture_specular, tex);
		}

		obj = new SceneObj(m_RootObj.get(), dynamic_cast<Sprite*>(new CubeSprite()), "cube2");
		obj->SetPosition(glm::vec3(-7.f, 1.4f, 1.4f));
		material = dynamic_cast<Material*>(obj->GetSprite());
		if (material)
		{
			LM::Texture* tex = Renderer::LoadTexture("./res/img/normalTex1.jpg", LM::texture_normal);
			material->SetTexture(LM::texture_normal, tex);
			tex = Renderer::LoadTexture("./res/img/img_2.png", LM::texture_diffuse);
			material->SetTexture(LM::texture_diffuse, tex);
		}
		// sphere
		obj = new SceneObj(m_RootObj.get(), dynamic_cast<Sprite*>(new SphereSprite()), "sphere");
		obj->SetPosition(glm::vec3(-2.0, 2.0f, -2.0f));
		obj = new SceneObj(m_RootObj.get(), dynamic_cast<Sprite*>(new SphereSprite()), "sphere3");
		obj->SetPosition(glm::vec3(20.0, 0.f, 0.0f));
		// ��Դ
		Illuminant* lightedObj = new Illuminant(m_RootObj.get(), nullptr, "DirLight1", 
			dynamic_cast<LM::Light*>(new LM::DirLight()));
		AddLight(lightedObj->GetLight());

		lightedObj = new Illuminant(m_RootObj.get(), new CubeSprite(), "PointLight1",
			dynamic_cast<LM::Light*>(new LM::PointLight()));
		lightedObj->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		lightedObj->SetPosition(glm::vec3(0.0f, 5.0f, 0.f));
		AddLight(lightedObj->GetLight());

		lightedObj = new Illuminant(m_RootObj.get(), new CubeSprite(), "SpotLight1",
			dynamic_cast<LM::Light*>(new LM::SpotLight()));
		lightedObj->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		lightedObj->SetPosition(glm::vec3(2.0f, 5.0f, 0.f));
		AddLight(lightedObj->GetLight());

	}
	void LightedDemoScene::LightEditor()
	{
	}
	LightedDemoScene::LightedDemoScene()
		:DemoSceneA(false),
		m_DirLightBuffer(0, (LM::Light*)nullptr, LM::LightType::DirectionLight),
		m_PointLightBuffer(0, (LM::Light*)nullptr, LM::LightType::PointLight),
		m_SpotLightBuffer(0, (LM::Light*)nullptr, LM::LightType::SpotLight),
		m_DirLights(), 
		m_PointLights(),
		m_SpotLights()
	{
		Init();
	}
	LightedDemoScene::LightedDemoScene(bool init)
		:DemoSceneA(false),
		m_DirLightBuffer(0, (LM::Light*)nullptr, LM::LightType::DirectionLight),
		m_PointLightBuffer(0, (LM::Light*)nullptr, LM::LightType::PointLight),
		m_SpotLightBuffer(0, (LM::Light*)nullptr, LM::LightType::SpotLight),
		m_DirLights(),
		m_PointLights(),
		m_SpotLights()
	{
		if (init)
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
	void LightedDemoScene::Update(float deltaTime)
	{
		DemoSceneA::Update(deltaTime);
		if(m_DirLights.size() > 0)
			m_DirLightBuffer.Init(m_DirLights.size(), &m_DirLights[0]);
		if (m_PointLights.size() > 0)
			m_PointLightBuffer.Init(m_PointLights.size(), &m_PointLights[0]);
		if (m_SpotLights.size() > 0)
			m_SpotLightBuffer.Init(m_SpotLights.size(), &m_SpotLights[0]);
	}
	bool LightedDemoScene::RemoveLight(LM::Light* light)
	{
		std::vector<LM::Light*>* lights;
		bool ret = false;
		switch (light->GetLightType())
		{
		case LM::LightType::DirectionLight:	lights = &m_DirLights; break;
		case LM::LightType::PointLight:		lights = &m_PointLights; break;
		case LM::LightType::SpotLight:		lights = &m_SpotLights; break;
		default:lights = nullptr; break;
		}
		if (lights)
		{
			for (auto iter = lights->begin(); iter != lights->end(); iter++)
			{
				if (*iter == light)
				{
					ret = true;
					lights->erase(iter);
					break;
				}
			}
		}
		return ret;
	}
	void LightedDemoScene::AddLight(LM::Light* light)
	{
		switch (light->GetLightType())
		{
		case LM::LightType::DirectionLight:	m_DirLights.push_back(light); break;
		case LM::LightType::PointLight:		m_PointLights.push_back(light); break;
		case LM::LightType::SpotLight:		m_SpotLights.push_back(light); break;
		default:break;
		}
	}
	void LightedDemoScene::AddIlluminant(Illuminant* obj)
	{
		m_RootObj->PushChild(obj);
		AddLight(obj->GetLight());
	}
	void LightedDemoScene::BindLightBuffer()
	{
		m_DirLightBuffer.BindToShaderStorage(nullptr, "");
		m_PointLightBuffer.BindToShaderStorage(nullptr, "");
		m_SpotLightBuffer.BindToShaderStorage(nullptr, "");
	}
}