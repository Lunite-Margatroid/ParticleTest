#pragma once
#include "QuadSprite.h"
#include "ElementBuffer.h"

namespace ptt
{
	class CubeSprite : public QuadSprite
	{
	protected:
		LM::ElementBuffer m_ebo;
		virtual void Init() override;
	public:
		CubeSprite(bool init = true);
		virtual void Render(const glm::mat4& modelTrans) override;
	};
}