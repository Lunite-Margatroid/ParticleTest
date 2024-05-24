#pragma once
#include "DemoSceneA.h"
#include "SceneObj/illuminant.h"
#include "glObj/LightBuffer.h"
#include "Light/Light.h"
#include "Sprite/SphereSprite.h"
namespace ptt
{
	class LightedDemoScene : public DemoSceneA
	{
	protected:
		LightBuffer m_DirLightBuffer;
		LightBuffer m_PointLightBuffer;
		LightBuffer m_SpotLightBuffer;

		std::vector<LM::Light*> m_DirLights;
		std::vector<LM::Light*> m_PointLights;
		std::vector<LM::Light*> m_SpotLights;

		virtual void Init() override;
		virtual void LightEditor();

	public:
		LightedDemoScene();
		virtual ~LightedDemoScene();
		virtual void RenderImGui() override;

		virtual void Update(float deltaTime) override;

		bool RemoveLight(LM::Light* light);
		void AddLight(LM::Light* light);

		virtual void BindLightBuffer();
	};
}