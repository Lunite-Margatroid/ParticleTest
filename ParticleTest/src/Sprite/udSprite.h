#pragma once
#include "Sprite.h"
namespace ptt
{
	class udSprite: virtual public Sprite
	{
	public:
		virtual void Update(float deltaTime);
	};
}