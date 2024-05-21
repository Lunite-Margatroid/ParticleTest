#pragma once
#include "Shader/Shader.h"
#include "Interface/ImGuiInterface.h"
namespace ptt
{
	class Sprite : public ImGuiInterface
	{
	protected:
		LM::Shader* m_Shader;	// »ﬂ”‡ «®“∆µƒ ±∫Úº«µ√…æµÙ
		bool m_Transparency;
		bool m_Visible;
		bool m_Lighted;
	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(const glm::mat4& modelTrans);

		bool IsTransparency() const;
		bool IsVisible()const;
		bool SetVisible(bool visible);
		void SetTransparency(bool transparency);
		bool IsLighted() const;
		void SetLighted(bool lighted);

		virtual void RenderImGui() override;
	};
}