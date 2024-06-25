#include "pch.h"
#include "Sprite.h"
#include "Renderer/Renderer.h"
namespace ptt
{
	Sprite::Sprite():m_Transparency(false),m_Visible(true),m_Lighted(false), m_ShaderName(LM::Shaders::Mesh_P_N_T)
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
	void Sprite::ShaderSelector()
	{
		if (
			ImGui::BeginCombo(
				"Shader Selector", 
				Renderer::GetShaderName(m_ShaderName).c_str()
					) 
			)
		{
			std::unordered_map<LM::Shaders, std::string> shaderNames = Renderer::GetShaderNames();
			for (auto& iter : shaderNames)
			{
				bool isSelected = iter.first == m_ShaderName;
				if (ImGui::Selectable(iter.second.c_str(), isSelected))
				{// process selected event
					m_ShaderName = iter.first;
				}
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}
	void Sprite::RenderImGui()
	{
		ImGui::Checkbox("Visible", &m_Visible);
		ImGui::SameLine();
		ImGui::Checkbox("Transparency", &m_Transparency);
		ShaderSelector();
	}
	void Sprite::SelectShader()
	{
		m_Shader = Renderer::GetShader(m_ShaderName);
	}
	void Sprite::Update(float deltaTime)
	{

	}
	LM::Shaders Sprite::GetShaderName() const
	{
		return m_ShaderName;
	}
	void Sprite::SetShaderName(LM::Shaders shaderName)
	{
		m_ShaderName = shaderName;
	}
}