#pragma once
#include "Shader.h"
namespace ptt
{
	class Sprite
	{
	protected:
		LM::Shader* m_Shader;
	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(glm::mat4& modelTrans);
	};
}