#pragma once
#include "ImGuiDialogModal.h"
#include "glObj/CubeTexture.h"

namespace ptt
{
	class SkyboxEditor : public ImGuiDialogModal
	{
	protected:
		std::map<GLenum, std::string> m_NameMap;
		GLenum m_Targets[6];

		unsigned int m_PreviewImg;
		int m_Width, m_Height;

		CubeTexture* m_CubeTexture;

		GLenum m_SelectedTarget;

		LM::Texture* m_PreTexture;

		void Init();
	public:
		SkyboxEditor(const std::string& key = "Skybox Editor");
		~SkyboxEditor();
		void ShowWindow() override;

		void SetCubeTexture(CubeTexture* cubeTexture);
		void UpdatePreview();
	};
}