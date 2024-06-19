#pragma once
#include "ImGuiDialogModal.h"
#include "glObj/Texture.h"

namespace ptt
{
	class TextureLoadDialog: public ImGuiDialogModal
	{
	protected:
		LM::Texture* m_tTexture;
		char m_tTextureName[128];
		char m_FilePath[256];

		// filter
		GLenum m_MagFilter;
		GLenum m_MinFilter;
		GLenum m_MagFilters[2];
		GLenum m_MinFilters[6];

		// wrap
		GLenum m_Wrap;
		GLenum m_WrapTypes[5];
		// y inverse
		bool m_YInverse;

		

		// texture type
		LM::TextureType m_TexTypes[4];
		LM::TextureType m_tTexType;

		std::map<unsigned int, std::string> m_NameMap;
	public:
		TextureLoadDialog(const std::string& key = "Load Texture");
		~TextureLoadDialog();

		void ShowWindow() override;
	};
}