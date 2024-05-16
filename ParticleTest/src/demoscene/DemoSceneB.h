#pragma once
#include "DemoSceneA.h"
#include "Sprite/ColoredSprite.h"
namespace ptt
{
	class DemoSceneB :public DemoSceneA
	{
	protected:

		virtual void Init() override;
	public:
		DemoSceneB();
		virtual ~DemoSceneB();
		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}