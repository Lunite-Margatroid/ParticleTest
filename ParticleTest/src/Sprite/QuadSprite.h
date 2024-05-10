#pragma once
#include "Sprite.h"
#include "ColoredSprite.h"
#include "Interface/ImGuiInterface.h"

namespace ptt
{
	class QuadSprite :public ColoredSprite<1>, public ImGuiInterface
	{
	public:
		QuadSprite();
		virtual ~QuadSprite();
		virtual void Render(const glm::mat4& modelTrans) override;
		virtual void RenderImGui() override;
	};
}