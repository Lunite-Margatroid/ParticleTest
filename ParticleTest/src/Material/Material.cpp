#include "pch.h"
#include "Material.h"

namespace ptt
{
	void Material::Init()
	{
		m_texDiffuse = Renderer::GetTexture("default texture");
		m_texSpecular = Renderer::GetTexture("default specular texture");
		m_texNormal = Renderer::GetTexture("default normal texture");
		m_texParallax = Renderer::GetTexture("default parallax texture");
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
		LM::Texture* tex = Renderer::GetTexture(texName);
		if (tex->GetTextureType() != texType)
		{
			// 纹理类型不匹配
			return;
		}

		switch (texType)
		{
		case LM::texture_diffuse:
			m_texDiffuse.m_Texture = tex;
			break;
		case LM::texture_specular:
			m_texSpecular.m_Texture = tex;
			break;
		case LM::texture_normal:
			m_texNormal.m_Texture = tex;
			break;
		case LM::texture_parallax:
			m_texParallax.m_Texture = tex;
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
					{// 选择事件
						if(textures[i].m_Texture->GetTextureType() == pTex.second->GetTextureType())
						{textures[i].m_Texture = pTex.second; }
						else
						{
							// 纹理类型不匹配
						}
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
			ImGui::Separator();
		}
		ImGui::DragFloat("shininess", &m_Shininess, 0.5, 1.0f, 64.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);

		ImGui::EndChild();

	}

	void Material::BindTexture()
	{
		Texture* textures = &m_texDiffuse;
		for (int i = 0; i < 4; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].m_Texture->GetTexID());
		}

	}

	void Material::SetUniformMaterial(LM::Shader* shader)
	{
		/*
		struct Material
		{
			sampler2D DiffuseTex;
			vec2 DiffuseTexOffset;
			vec2 DiffuseTexScale;
	
			sampler2D SpecularTex;
			vec2 SpecularTexOffset;
			vec2 SpecularTexScale;
	
			sampler2D NormalTex;
			vec2 NormalTexOffset;
			vec2 NormalTexScale;
	
			sampler2D ParallaxTex;
			vec2 ParallaxTexOffset;
			vec2 ParallaxTexScale;
	
			float shininess;
		};

		uniform Material u_Material;
		*/
		BindTexture();
		shader->Bind();
		shader->SetUniformTexture("u_Material.DiffuseTex", 0);
		shader->SetUniform2f("u_Material.DiffuseTexOffset", &m_texDiffuse.offsetx);
		shader->SetUniform2f("u_Material.DiffuseTexScale", &m_texDiffuse.scalex);

		shader->SetUniformTexture("u_Material.SpecularTex", 1);
		shader->SetUniform2f("u_Material.SpecularTexOffset", &m_texSpecular.offsetx);
		shader->SetUniform2f("u_Material.SpecularTexScale", &m_texSpecular.scalex);

		shader->SetUniformTexture("u_Material.NormalTex", 2);
		shader->SetUniform2f("u_Material.NormalTexOffset", &m_texNormal.offsetx);
		shader->SetUniform2f("u_Material.NormalTexScale", &m_texNormal.scalex);

		shader->SetUniformTexture("u_Material.ParallaxTex", 3);
		shader->SetUniform2f("u_Material.ParallaxTexOffset", &m_texParallax.offsetx);
		shader->SetUniform2f("u_Material.ParallaxTexScale", &m_texParallax.scalex);

		shader->SetUniform1f("u_Material.shininess", m_Shininess);
	}
}
