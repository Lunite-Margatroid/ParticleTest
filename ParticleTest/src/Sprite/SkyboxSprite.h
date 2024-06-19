#pragma once
#include "Sprite.h"
#include "VertexArray.h"
#include "glObj/CubeTexture.h"

namespace ptt
{
	class SkyboxSprite : public Sprite
	{
	protected:
		LM::VertexArray* m_vao;
		CubeTexture m_CubeTexture;

		void Init();
	public:
		SkyboxSprite();
		void Render(const glm::mat4& modelTrans) override;
		void RenderSkybox();
		void RenderImGui() override;
	};
}