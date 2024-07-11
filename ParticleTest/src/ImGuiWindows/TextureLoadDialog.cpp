#include "pch.h"
#include "TextureLoadDialog.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "Renderer/Renderer.h"
namespace ptt
{
	TextureLoadDialog::TextureLoadDialog(const std::string& key)
		:ImGuiDialogModal(key)
	{
		m_Open = true;
		memset(m_FilePath, 0, 256);
		memset(m_tTextureName, 0, 128);

		m_NameMap[GL_NEAREST] = std::string("Nearest");
		m_NameMap[GL_LINEAR] = std::string("Linear");
		m_NameMap[GL_NEAREST_MIPMAP_NEAREST] = std::string("Nearest Mipmap Nearest Pixel");
		m_NameMap[GL_LINEAR_MIPMAP_NEAREST] = std::string("Linear Mipmap Nearest Pixel");
		m_NameMap[GL_NEAREST_MIPMAP_LINEAR] = std::string("Nearest Mipmap Linear Pixel");
		m_NameMap[GL_LINEAR_MIPMAP_LINEAR] = std::string("Linear Mipmap Linear Pixel");

		m_MagFilters[0] = GL_NEAREST;
		m_MagFilters[1] = GL_LINEAR;

		m_MinFilters[0] = GL_NEAREST;
		m_MinFilters[1] = GL_LINEAR;
		m_MinFilters[2] = GL_NEAREST_MIPMAP_NEAREST;
		m_MinFilters[3] = GL_LINEAR_MIPMAP_NEAREST;
		m_MinFilters[4] = GL_NEAREST_MIPMAP_LINEAR;
		m_MinFilters[5] = GL_LINEAR_MIPMAP_LINEAR;

		m_TexTypes[0] = LM::texture_diffuse;
		m_TexTypes[1] = LM::texture_specular;
		m_TexTypes[2] = LM::texture_normal;
		m_TexTypes[3] = LM::texture_parallax;

		m_NameMap[LM::texture_diffuse] = std::string("Diffuse Texture");
		m_NameMap[LM::texture_normal] = std::string("Normal Texture");
		m_NameMap[LM::texture_specular] = std::string("Specular Texture");
		m_NameMap[LM::texture_parallax] = std::string("Parallax Texture");

		m_NameMap[GL_CLAMP_TO_EDGE] = std::string("Clamp To Edge"); 
		m_NameMap[GL_CLAMP_TO_BORDER] = std::string("Clamp To Border");
		m_NameMap[GL_MIRRORED_REPEAT] = std::string("Mirrored Repeat");
		m_NameMap[GL_REPEAT] = std::string("Repeat"); 
		m_NameMap[GL_MIRROR_CLAMP_TO_EDGE] = std::string("Mirror Clamp To Edge");
		
		m_WrapTypes[0] = GL_CLAMP_TO_EDGE;
		m_WrapTypes[1] = GL_CLAMP_TO_BORDER;
		m_WrapTypes[2] = GL_MIRRORED_REPEAT;
		m_WrapTypes[3] = GL_REPEAT;
		m_WrapTypes[4] = GL_MIRROR_CLAMP_TO_EDGE;


		m_MagFilter = GL_NEAREST;
		m_MinFilter = GL_NEAREST;

		m_tTexType = LM::texture_diffuse;
		m_Wrap = GL_REPEAT;
		m_YInverse = true;

		m_tTexture = new LM::Texture();
		
	}
	TextureLoadDialog::~TextureLoadDialog()
	{
		if (m_tTexture)
			delete m_tTexture;
	}
	void TextureLoadDialog::ShowWindow()
	{
		// ImGui::BeginPopupModal(m_keyString.c_str());

		if (WindowBegin())
		{
			ImGui::InputText("##FilePath", m_FilePath, 256); ImGui::SameLine();
			if (ImGui::Button("Select File"))
			{
				IGFD::FileDialogConfig config;
				config.path = "./";
				config.flags |= ImGuiFileDialogFlags_Modal;
				ImGuiFileDialog::Instance()->OpenDialog("Load Texture", "Choose File", ".jpg,.png,.bmp,.*", config);
			}
			ImGui::InputText("Texture Name", m_tTextureName, 128);

			// filter
			// mag filter
			if(ImGui::BeginCombo("Mag Filter", m_NameMap[m_MagFilter].c_str()))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = m_MagFilter == m_MagFilters[i];
					if (ImGui::Selectable(m_NameMap[m_MagFilters[i]].c_str(), &isSelected))
					{
						m_MagFilter = m_MagFilters[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			// min filter
			if (ImGui::BeginCombo("Min Filter", m_NameMap[m_MinFilter].c_str()))
			{
				for (int i = 0; i < 6; i++)
				{
					bool isSelected = m_MinFilter == m_MinFilters[i];
					if (ImGui::Selectable(m_NameMap[m_MinFilters[i]].c_str(), &isSelected))
					{
						m_MinFilter = m_MinFilters[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			// texture type
			if (ImGui::BeginCombo("Texture Type", m_NameMap[m_tTexType].c_str()))
			{
				for (int i = 0; i < 4; i++)
				{
					bool isSelected = m_tTexType == m_TexTypes[i];
					if (ImGui::Selectable(m_NameMap[m_TexTypes[i]].c_str(), &isSelected))
					{
						m_tTexType = m_TexTypes[i];
						
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			if (ImGui::BeginCombo("Wrap Type", m_NameMap[m_Wrap].c_str()))
			{
				for (int i = 0; i < 5; i++)
				{
					bool isSelected = m_Wrap == m_WrapTypes[i];
					if (ImGui::Selectable(m_NameMap[m_WrapTypes[i]].c_str(), &isSelected))
					{
						m_Wrap = m_WrapTypes[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Checkbox("Inverse Y Axis", &m_YInverse);

			// preview
			if (ImGui::Button("Refresh"))
			{
				if (m_tTexture)
					delete m_tTexture;
				m_tTexture = new LM::Texture(m_FilePath, m_tTexType, GL_RGBA, GL_RGB, m_MinFilter, m_MagFilter, m_Wrap, m_YInverse);
				
			}

			int width = m_tTexture->GetWidth();
			int height = m_tTexture->GetHeight();
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
					(void*)m_tTexture->GetTexID(),
					drawPos,
					ImVec2(drawPos.x + width, drawPos.y + height),
					ImVec2(0,1),
					ImVec2(1,0)
					);

			ImGui::EndChild();

			if (ImGuiFileDialog::Instance()->Display("Load Texture")) {
				if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
					std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
					// action
					memset(m_FilePath, 0, 256);
					ASSERT(filePathName.size() < 256);
					memcpy(m_FilePath, filePathName.c_str(), filePathName.size());

					int offset = filePathName.find_last_of('\\') + 1;
					std::string tFileName = filePathName.substr(offset, filePathName.length() - offset);
					memset(m_tTextureName, 0, 128);
					ASSERT(tFileName.size() < 128);
					memcpy(m_tTextureName, tFileName.c_str(), tFileName.size());

					if (m_tTexture)
						delete m_tTexture;
					m_tTexture = new LM::Texture(m_FilePath, m_tTexType, GL_RGBA, GL_RGB, m_MinFilter, m_MagFilter, m_Wrap, m_YInverse);
					m_tTexture->SetTextureName(m_tTextureName);
				}

				// close
				ImGuiFileDialog::Instance()->Close();
			}

			if (ImGui::Button("Load"))
			{
				m_tTexture->SetTextureName(m_tTextureName);
				m_tTexture->SetTextureType(m_tTexType);
				Renderer::SaveTexture(m_tTexture);
				m_tTexture = new LM::Texture();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		/*bool b = ImGui::BeginPopupEx(m_ImGui_ID, flags);
		if (b)
		{
			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}*/
	}
}
