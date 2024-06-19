#include "pch.h"
#include "TextureSelector.h"
#include "Renderer/Renderer.h"
#include "Application.h"

namespace ptt
{
	void TextureSelector::Init()
	{
		m_SelectedTexture = Renderer::GetTexture();
		m_WritingTarget = nullptr;
	}
	TextureSelector::TextureSelector(const std::string& key)
		:ImGuiDialogModal(key)
	{
		Init();
	}
	TextureSelector::~TextureSelector()
	{
	}
	void TextureSelector::ShowWindow()
	{
		if (WindowBegin())
		{
			const auto& textures = Renderer::GetTextureMap();
			if (ImGui::BeginCombo("Select Texture", m_SelectedTexture->GetTextureName().c_str()))
			{
				for (const auto& tex : textures)
				{
					bool isSelected = m_SelectedTexture == tex.second;
					if (ImGui::Selectable(tex.first.c_str(), &isSelected))
					{
						m_SelectedTexture = tex.second;
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				// load texture
				if (ImGui::Selectable("# Load texture ..."))
				{
					Application::OpenDialog("Texture Load");
				}
				ImGui::EndCombo();
			}
			Application::ShowDialog("Texture Load");

			int width = m_SelectedTexture->GetWidth();
			int height = m_SelectedTexture->GetHeight();

			float aspectRatio = (float)width / height;
			width = width > 1000 ? 1000 : width;
			width = width < 300 ? 300 : width;
			height = height > 500 ? 500 : height;
			height = height < 200 ? 200 : height;
			if ((float)width / height > aspectRatio)
			{
				width = height * aspectRatio;
			}
			else
			{
				height = width / aspectRatio;
			}

			ImGui::BeginChild("Texture Preview", ImVec2(width, height));
			ImVec2 drawPos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddImage
			(
				(void*)m_SelectedTexture->GetTexID(),
				drawPos,
				ImVec2(drawPos.x + width, drawPos.y + height),
				ImVec2(0, 0),
				ImVec2(1, 1)
			);
			ImGui::EndChild();

			if (ImGui::Button("OK"))
			{
				if (m_WritingTarget)
				{
					*m_WritingTarget = m_SelectedTexture;
				}
				ImGui::CloseCurrentPopup();
			}ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}

			WindowEnd();
		}
	}
	void TextureSelector::InitWindow(LM::Texture** writingTarget)
	{
		m_WritingTarget = writingTarget;
	}
}