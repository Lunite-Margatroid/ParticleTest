#include "pch.h"
#include "Material.h"

namespace ptt
{
	void Material::Init()
	{
	}
	Material::Material()
		:m_texDiffuse(nullptr),
		m_texSpecular(nullptr),
		m_texNormal(nullptr),
		m_texParallax(nullptr),
		m_Shininess(16.0f)
	{
		Init();
	}
	Material::~Material()
	{
	}
	void Material::SetTexture(LM::TextureType texType, const std::string& texName)
	{
		switch (texType)
		{
		case LM::texture_diffuse:
			m_texDiffuse.m_Texture = Renderer::GetTexture(texName);
			break;
		case LM::texture_specular:
			m_texSpecular.m_Texture = Renderer::GetTexture(texName);
			break;
		case LM::texture_normal:
			m_texNormal.m_Texture = Renderer::GetTexture(texName);
			break;
		case LM::texture_parallax:
			m_texParallax.m_Texture = Renderer::GetTexture(texName);
			break;
		default:
			break;
		}
	}

	void Material::MaterialEditor()
	{
		const std::unordered_map<std::string, LM::Texture*>& textureMap = Renderer::GetTextureMap();
		Texture* textures;
		textures = (Texture*)&m_texDiffuse;
		ImGui::BeginChild("Material Editor",
			ImVec2(0.0f, 0.0f),
			ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY);
		for (int i = 0; i < 4; i++)
		{// 对于每一个 m_Texture 都有一个combo
			
			if (ImGui::BeginCombo(textures[i].m_Texture->GetTexType().c_str(), textures[i].m_Texture->GetTextureName().c_str()))
			{
				int n = Renderer::GetTextureCount();
				for (const auto& pTex : textureMap) // 遍历renderer所有纹理
				{
					bool isSelected = (pTex.second == textures[i].m_Texture);// 与当前纹理是同一个 isSelected = true
					if (ImGui::Selectable(pTex.first.c_str(), isSelected))
					{
						textures[i].m_Texture = pTex.second;
					}
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::DragFloat2("offset", &textures[i].offsetx, 0.01f, 0.0f, 1.0f,
				"%.3f",
				ImGuiSliderFlags_AlwaysClamp);
			ImGui::DragFloat2("scale", &textures[i].scalex, 0.05f, 0.05f, 10.0f,
				"%.3f",
				ImGuiSliderFlags_AlwaysClamp);
			ImGui::DragFloat("weight", &textures[i].weight, 0.05f, 0.00f, 10.0f,
				"%.3f",
				ImGuiSliderFlags_AlwaysClamp);
		}
		ImGui::EndChild();

	}
}
