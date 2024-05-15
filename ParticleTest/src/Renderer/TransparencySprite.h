#pragma once
#include "Sprite/Sprite.h"
namespace ptt
{
	class TransparencySprite
	{
		const glm::mat4& m_ModelTrans;
		Sprite* m_Sprite;
	public:
		explicit TransparencySprite(Sprite* sprite, const glm::mat4& modelTrans);
		void operator() () const;
	};
}