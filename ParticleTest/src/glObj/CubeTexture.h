#pragma once
#include "Texture.h"

namespace ptt
{
	class CubeTexture
	{
	protected:
		unsigned int m_uTextureID;
		
		int m_Width, m_Height;

	public:
		CubeTexture();
		~CubeTexture();

		void LoadTexture(const std::string& path, GLenum target);
		void LoadTexture(void* data, int width, int height, GLenum target, GLenum format, GLenum dataType);
		void LoadTexture(LM::Texture* texture2D, GLenum target);

		void Bind();
		unsigned int GetTexID();
		std::pair<int, int> GetSize(GLenum target) const;

		void Refresh();
	};
}