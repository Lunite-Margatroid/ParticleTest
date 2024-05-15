#pragma once
#include "Shader/Shader.h"
#include "Interface/ImGuiInterface.h"
namespace ptt
{
	class Sprite : public ImGuiInterface
	{
	protected:
		LM::Shader* m_Shader;	// ���� Ǩ�Ƶ�ʱ��ǵ�ɾ��
		bool m_Transparency;
		bool m_Visible;
	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(const glm::mat4& modelTrans);

		bool IsTransparency() const;
		bool IsVisible()const;
		bool SetVisible(bool visible);

		virtual void RenderImGui() override;
	};
}