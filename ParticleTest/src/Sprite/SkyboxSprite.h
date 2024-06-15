#pragma once
#include "Sprite.h"
#include "VertexArray.h"

namespace ptt
{
	class SkyboxSprite : public Sprite
	{
	protected:
		LM::VertexArray* m_vao;

		void Init();
	public:
		void Render(const glm::mat4& modelTrans) override;
		void RenderSkybox();
	};
}