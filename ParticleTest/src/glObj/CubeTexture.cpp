#include "pch.h"
#include "CubeTexture.h"
// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <wchar.h>
#include <codecvt>

namespace ptt
{
	CubeTexture::CubeTexture()
	{
		GLCall(glGenTextures(1, &m_uTextureID));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID));

		unsigned char tData[4];
		memset(tData, 0xff, 4);

		for (int i = 0; i < 6; i++)
			LoadTexture(tData, 1, 1, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, GL_RGB, GL_UNSIGNED_BYTE);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	CubeTexture::~CubeTexture()
	{
		GLCall(glDeleteTextures(1, &m_uTextureID));
	}
	void CubeTexture::LoadTexture(const std::string& path, GLenum target)
	{
		int nChannals;
		unsigned char* data = NULL;
		stbi_set_flip_vertically_on_load(false);	// ·­×ªyÖá
		int width, height;

		/*-------------- load data --------------*/
		std::wstring wstr;
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		wstr = wcv.from_bytes(path);

		FILE* f;
		_wfopen_s(&f, wstr.c_str(), L"rb");	// ¿í×Ö·û°æµÄopen file

		if (f)
		{
			data = stbi_load_from_file(f, &width, &height, &nChannals, 0);
			fclose(f);
		}
		if (data == NULL)
		{
			std::cout << "Fail to load img!" << std::endl;
			std::wcout << wstr << std::endl;
			return;
		}

		Bind();
		GLenum srcFormat = GL_RGB;
		if (nChannals == 4)
			srcFormat = GL_RGBA;
		glTexImage2D(target, 0, GL_RGB, width, height, 0, srcFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	void CubeTexture::LoadTexture(void* data, int width, int height, GLenum target, GLenum foramt, GLenum dataType)
	{
		Bind();
		glTexImage2D(target, 0, GL_RGB, width, height, 0, foramt, dataType, data);
	}
	void CubeTexture::LoadTexture(LM::Texture* texture2D, GLenum target)
	{
		Bind();
		int width = texture2D->GetWidth();
		int height = texture2D->GetHeight();
		unsigned char* data = new unsigned char[width * height];
		glBindTexture(GL_TEXTURE_2D, texture2D->GetTexID());
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		delete[] data;
	}
	void CubeTexture::Bind()
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID));
	}
	unsigned int CubeTexture::GetTexID()
	{
		return m_uTextureID;
	}
}