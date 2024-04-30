#pragma once
#include "Shader/Shader.h"
namespace ptt
{
	class Sprite
	{
	protected:
		LM::Shader* m_Shader;	// 冗余 迁移的时候记得删掉
	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(const glm::mat4& modelTrans);
	};
}