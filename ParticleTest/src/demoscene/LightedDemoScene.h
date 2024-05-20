#pragma once
#include "DemoSceneA.h"
namespace ptt
{
	class LightedDemoScene : public DemoSceneA
	{
	protected:

		virtual void Init() override;

		virtual void LightEditor();

	public:
		LightedDemoScene();
		virtual ~LightedDemoScene();
		virtual void RenderImGui() override;
	};
}