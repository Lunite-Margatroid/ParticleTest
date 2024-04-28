#pragma once
#include "demoscene/SpriteTest.h"
#include "Sprite/FireWork.h"
namespace ptt
{
	class FireworkScene :public SpriteTest
	{
	public:
		FireworkScene();
		virtual ~FireworkScene();

		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}