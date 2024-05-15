#include "pch.h"
#include "TransparencySprite.h"

namespace ptt
{
	TransparencySprite::TransparencySprite(Sprite* sprite, const glm::mat4& modelTrans)
		:m_Sprite(sprite), m_ModelTrans(modelTrans)
	{}
	void TransparencySprite::operator() () const
	{
		m_Sprite->Render(m_ModelTrans);
	}
}