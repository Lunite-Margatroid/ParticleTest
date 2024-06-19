#include "pch.h"
#include "SkyboxEditor.h"
#include "Application.h"
#include "TextureSelector.h"

namespace ptt
{
	void SkyboxEditor::Init()
	{
		for (int i = 0; i < 6; i++)
		{
			m_Targets[i] = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		}
		m_NameMap[GL_TEXTURE_CUBE_MAP_POSITIVE_X] = std::string("Positive X Axis");
		m_NameMap[GL_TEXTURE_CUBE_MAP_NEGATIVE_X] = std::string("Negative X Axis");
		m_NameMap[GL_TEXTURE_CUBE_MAP_POSITIVE_Y] = std::string("Positive Y Axis");
		m_NameMap[GL_TEXTURE_CUBE_MAP_NEGATIVE_Y] = std::string("Negative Y Axis");
		m_NameMap[GL_TEXTURE_CUBE_MAP_POSITIVE_Z] = std::string("Positive Z Axis");
		m_NameMap[GL_TEXTURE_CUBE_MAP_NEGATIVE_Z] = std::string("Negative Z Axis");

		m_SelectedTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;

		m_CubeTexture = nullptr;
		m_PreTexture = nullptr;
	}
	SkyboxEditor::SkyboxEditor(const std::string& key)
		:ImGuiDialogModal(key)
	{
		glGenTextures(1, &m_PreviewImg);
		glBindTexture(GL_TEXTURE_2D, m_PreviewImg);

		Init();
	}
	SkyboxEditor::~SkyboxEditor()
	{
		glDeleteTextures(1, &m_PreviewImg);
	}
	void SkyboxEditor::ShowWindow()
	{
		if (WindowBegin())
		{
			if (ImGui::BeginCombo("Skybox Face", m_NameMap[m_SelectedTarget].c_str()))
			{
				for (int i = 0; i < 6; i++)
				{
					bool isSelected = m_SelectedTarget == m_Targets[i];
					if (ImGui::Selectable(m_NameMap[m_Targets[i]].c_str(), &isSelected))
					{
						m_SelectedTarget = m_Targets[i];
						UpdatePreview();
					}
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Texture Selector"))
			{
				Application::OpenDialog("Texture Selector");
				TextureSelector*dialog = dynamic_cast<TextureSelector*>(Application::GetDialog("Texture Selector"));
				if (dialog)
				{
					dialog->InitWindow(&m_PreTexture);
				}
			}
			Application::ShowDialog("Texture Selector");

			int width = m_Width;
			int height = m_Height;

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
				(void*)m_PreviewImg,
				drawPos,
				ImVec2(drawPos.x + width, drawPos.y + height),
				ImVec2(0, 0),
				ImVec2(1, 1)
			);

			ImGui::EndChild();

			if(ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			WindowEnd();
		}
		// --------------- update -----------------
		if (m_PreTexture)
		{
			m_CubeTexture->LoadTexture(m_PreTexture, m_SelectedTarget);
			m_PreTexture = nullptr;
			m_CubeTexture->Refresh();
			UpdatePreview();
		}
	}
	void SkyboxEditor::SetCubeTexture(CubeTexture* cubeTexture)
	{
		m_CubeTexture = cubeTexture;
		UpdatePreview();
	}
	void SkyboxEditor::UpdatePreview()
	{

		std::pair<int, int> imgSize = m_CubeTexture->GetSize(m_SelectedTarget);
		m_Width = imgSize.first;
		m_Height = imgSize.second;
		unsigned char* data = new unsigned char[m_Width * m_Height* 3];
		m_CubeTexture->Bind();
		glGetTexImage(m_SelectedTarget, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, m_PreviewImg);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSize.first, imgSize.second, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);		// 设置环绕方式

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);	// 设置插值方式

		glGenerateMipmap(GL_TEXTURE_2D);	// 自动生成多级渐远级别纹理(mipmap)
	}
}