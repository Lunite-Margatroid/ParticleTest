#pragma once

#include "CubeSprite.h"

namespace ptt
{
	class SphereSprite : public CubeSprite
	{
	protected:
		void Init() override;
	public:
		SphereSprite(bool init);
		SphereSprite();

		void SelectShader() override;

	};
}