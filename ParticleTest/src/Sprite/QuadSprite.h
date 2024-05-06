#pragma once
#include "Sprite.h"
#include "ColoredSprite.h"


namespace ptt
{
	class QuadSprite :virtual public Sprite, public ColoredSprite<1>
	{
		
	
	};
}