#pragma once
#include "SceneObj.h"
#include "Light/SpotLight.h"

namespace ptt
{
	class Illuminant: public SceneObj
	{
	protected:
		LM::Light* m_Light;
	public:
		Illuminant(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name", LM::Light* light = nullptr);
		virtual ~Illuminant();
		void RenderImGui() override;

		virtual void Update(float deltaTime) override;

		void AttachLight(LM::Light* light);
		void RemoveLight();


	};
}