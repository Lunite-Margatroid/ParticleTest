#pragma once
#include "Shader/Shader.h"
namespace ptt
{
	class Sprite
	{
	protected:
		LM::Shader* m_Shader;	// ���� Ǩ�Ƶ�ʱ��ǵ�ɾ��
	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(const glm::mat4& modelTrans);
	};
}