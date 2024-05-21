#include "pch.h"
#include "Sprite.h"

namespace ptt
{
	Sprite::Sprite():m_Transparency(false),m_Visible(true),m_Lighted(false)
	{
	}
	Sprite::~Sprite()
	{
	}
	void Sprite::Render(const glm::mat4& modelTrans)
	{
	}
	bool Sprite::IsTransparency() const
	{
		return m_Transparency;
	}
	bool Sprite::IsVisible() const
	{
		return m_Visible;
	}
	bool Sprite::SetVisible(bool visible)
	{
		return m_Visible = visible;
	}
	void Sprite::SetTransparency(bool transparency)
	{
		m_Transparency = transparency;
	}
	bool Sprite::IsLighted() const
	{
		return m_Lighted;
	}
	void Sprite::SetLighted(bool lighted)
	{
		m_Lighted = lighted;
	}
	void Sprite::RenderImGui()
	{
		ImGui::SeparatorText("Sprite Property");
		ImGui::Checkbox("Visible", &m_Visible);
		ImGui::SameLine();
		ImGui::Checkbox("Transparency", &m_Transparency);
		ImGui::Checkbox("Lighted", &m_Lighted);
	}
}