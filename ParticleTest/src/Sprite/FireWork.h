#pragma once
#include "Sprite.h"

namespace ptt
{
	class FireWork:public Sprite
	{
	private:

	public:
		FireWork();
		~FireWork();

		virtual void Update(float deltaTime);
		virtual void Render(const glm::mat4& modelTrans) override;
	};


}