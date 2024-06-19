#include "pch.h"
#include "CubeTexture.h"
// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <wchar.h>
#include <codecvt>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image_resize.h>

namespace ptt
{
	CubeTexture::CubeTexture()
	{
		GLCall(glGenTextures(1, &m_uTextureID));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID));

		unsigned char tData[4];
		memset(tData, 0xff, 4);

		m_Width = m_Height = 2048;

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

		unsigned char* tempData = new unsigned char[m_Height * m_Width * nChannals];
		stbir_resize_uint8(data, width, height, 0, tempData, m_Width, m_Height, 0, nChannals);
		glTexImage2D(target, 0, GL_RGB, m_Width, m_Height, 0, srcFormat, GL_UNSIGNED_BYTE, tempData);

		stbi_image_free(data);

		delete[] tempData;
	}
	void CubeTexture::LoadTexture(void* data, int width, int height, GLenum target, GLenum format, GLenum dataType)
	{
		Bind();
		ASSERT(dataType == GL_UNSIGNED_BYTE);

		int nChannals = 3;
		if (format == GL_RGBA)
		{
			nChannals = 4;
		}
		unsigned char* tempData = new unsigned char[m_Height * m_Width * nChannals];
		stbir_resize_uint8((unsigned char*)data, width, height, 0, tempData, m_Width, m_Height, 0, nChannals);
		glTexImage2D(target, 0, GL_RGB, m_Width, m_Height, 0, format, dataType, tempData);
		delete[] tempData;
	}
	void CubeTexture::LoadTexture(LM::Texture* texture2D, GLenum target)
	{
		Bind();
		int width = texture2D->GetWidth();
		int height = texture2D->GetHeight();
		unsigned char* data = new unsigned char[width * height * 4];
		unsigned char* tempData = new unsigned char[m_Width * m_Height * 4];
		glBindTexture(GL_TEXTURE_2D, texture2D->GetTexID());
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbir_resize_uint8((unsigned char*)data, width, height, 0, tempData, m_Width, m_Height, 0, 4);
		glTexImage2D(target, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempData);

		delete[] data;
		delete[] tempData;

	}
	void CubeTexture::Bind()
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID));
	}
	unsigned int CubeTexture::GetTexID()
	{
		return m_uTextureID;
	}
	std::pair<int, int> CubeTexture::GetSize(GLenum target) const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID);
		return std::make_pair(m_Width, m_Height);
	}
	void CubeTexture::Refresh()
	{
		Bind();
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
}