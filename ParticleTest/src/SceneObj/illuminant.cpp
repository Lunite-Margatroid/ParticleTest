#include "pch.h"
#include "illuminant.h"
#include "Application.h"
#include "demoscene/LightedDemoScene.h"

namespace ptt
{
	Illuminant::Illuminant(SceneObj* parent, Sprite* sprite, const std::string& objName, LM::Light* light)
		:SceneObj(parent, sprite, objName),
		m_Light(light)
	{
		/*LightedDemoScene* scene = dynamic_cast<LightedDemoScene*>(Application::GetCurrentScene());
		if (scene)
		{
			scene->AddLight(m_Light);
		}*/
		//LightedDemoScene* scene = (LightedDemoScene*)(Application::GetCurrentScene());
		//scene->AddLight(m_Light);

		// 动态创建的时候要注意 保存光照对象
	}
	Illuminant::~Illuminant()
	{
		if (m_Light)
			delete m_Light;
	}
	void Illuminant::RenderImGui()
	{
		SceneObj::RenderImGui();
		if (m_Light)
			m_Light->LightEditor();
	}
	void Illuminant::Update(float deltaTime)
	{
		SceneObj::Update(deltaTime);

		// 光源的位置和朝向与Object一致
		if (m_Light)
		{
			LM::DirLight* dirLight = dynamic_cast<LM::DirLight*>(m_Light);
			if (dirLight)
			{
				dirLight->SetLightDirection(glm::mat3(m_ModelTrans) * glm::vec3(0.0, -1.0f, 0.0f));
			}
			LM::PointLight* pointLight = dynamic_cast<LM::PointLight*>(m_Light);
			if (pointLight)
			{
				pointLight->SetLightPosition(m_Position);
			}
		}
	}
	void Illuminant::AttachLight(LM::Light* light)
	{
		if (m_Light)
		{
			LightedDemoScene *scene = dynamic_cast<LightedDemoScene*>(Application::GetCurrentScene());
			if (scene)
			{
				scene->RemoveLight(m_Light);
				scene->AddLight(light);
			}
			delete m_Light;
		}
		m_Light = light;
	}
	void Illuminant::RemoveLight()
	{
		if (m_Light)
		{
			LightedDemoScene* scene = dynamic_cast<LightedDemoScene*>(Application::GetCurrentScene());
			if (scene)
			{
				scene->RemoveLight(m_Light);
			}
			delete m_Light;
			m_Light = nullptr;
		}
	}
	LM::Light* Illuminant::GetLight()
	{
		return m_Light;
	}
}