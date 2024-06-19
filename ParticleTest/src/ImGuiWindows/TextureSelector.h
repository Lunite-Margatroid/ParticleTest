#pragma once
#include "ImGuiDialogModal.h"
#include "glObj/Texture.h"

namespace ptt
{
	class TextureSelector : public ImGuiDialogModal
	{
	protected:
		LM::Texture* m_SelectedTexture;
		
		LM::Texture** m_WritingTarget;

		void Init();
	public:
		TextureSelector(const std::string& key = "Texture Selector");
		~TextureSelector();

		void ShowWindow() override;
		void InitWindow(LM::Texture** writingTarget);
	};
}