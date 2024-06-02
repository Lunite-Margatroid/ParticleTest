#include "pch.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Texture.h"
#include <wchar.h>
#include <codecvt>
namespace LM
{

	bool Texture::LoadTexture(unsigned int* texture, const std::string& path, unsigned char index, int texColorMode, int resColorMode, bool bGenerateMipmap, bool yReverse)
	{
		int nChannals;
		unsigned char* img_data = 0;
		stbi_set_flip_vertically_on_load(yReverse);	// 翻转y轴
		// 原点到了图片的左下角

		/*---------------- process path ----------------*/

		// utf-8转为宽字符
		std::wstring wstr;
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		wstr = wcv.from_bytes(path);

		FILE* f;
		_wfopen_s(&f, wstr.c_str(), L"rb");	// 宽字符版的open file

		if (f)
		{
			img_data = stbi_load_from_file(f, &m_nWidth, &m_nHeight, &nChannals, 0);
			fclose(f);
		}
		if (img_data == 0)
		{
			std::cout << "Fail to load img!" << std::endl;
			std::wcout << wstr << std::endl;
			return false;
		}
		/*---------------------------------------------*/

		/*img_data = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &nChannals, 0);

		if (img_data == 0)
		{
			std::cout << "Fail to load img!----" << path << std::endl;
			return false;
		}*/
		GLCall(glGenTextures(1, texture));
		GLCall(glActiveTexture(GL_TEXTURE0 + index));
		GLCall(glBindTexture(GL_TEXTURE_2D, *texture)); // 绑定纹理

		if (nChannals == 4) {
			resColorMode = GL_RGBA;
		}
		if (nChannals == 3) {
			resColorMode = GL_RGB;
		}
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texColorMode, m_nWidth, m_nHeight, 0, resColorMode, GL_UNSIGNED_BYTE, img_data));
		// param1 纹理Target
		// param2 多级渐远级别 0为基本级别
		// param3 纹理格式
		// param4&5 宽度和高度x&y
		// param6 历史遗留 恒为0
		// param7 源数据格式
		// param8 源数据类型
		// param9 源数据

		if (bGenerateMipmap)
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// 自动生成多级渐远级别纹理
		stbi_image_free(img_data);						// 释放图像资源
		return true;
	}

	Texture::Texture(const std::string& imgPath, TextureType type, GLenum dstColorMode, GLenum srcColorMode, GLenum minFilter, GLenum magFilter, GLenum wrap, bool yReverse)
		:m_type(type)
	{
		switch (m_type)
		{
		case LM::texture_unknown:
			m_strType = "texture_unknown";
			break;
		case LM::texture_diffuse:
			m_strType = "texture_diffuse";
			break;
		case LM::texture_specular:
			m_strType = "texture_specular";
			break;
		case LM::texture_normal:
			m_strType = "texture_normal";
			break;
		case LM::texture_parallax:
			m_strType = "texture_parallax";
			break;
		default:
			break;
		}

		bool ifMipmap;
		ifMipmap = minFilter == GL_NEAREST_MIPMAP_NEAREST ||
			minFilter == GL_LINEAR_MIPMAP_NEAREST ||
			minFilter == GL_NEAREST_MIPMAP_LINEAR ||
			minFilter == GL_LINEAR_MIPMAP_LINEAR;
		if (this->LoadTexture(&m_uTextureID, imgPath, 0, dstColorMode, srcColorMode, ifMipmap, yReverse))
		{
		}
		else
		{
			float errorColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};
			GLCall(glGenTextures(1, &m_uTextureID));
			GLCall(glActiveTexture(GL_TEXTURE0));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_uTextureID));
			m_nWidth = m_nHeight = 1;
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, dstColorMode, m_nWidth, m_nHeight, 0, GL_RGBA, GL_FLOAT, errorColor));
		}
		m_ubTextureIndex = 0;
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));		// 设置环绕方式

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter));	// 设置插值方式
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_uTextureID));
	}

	Texture::Texture(TextureType type):
		m_nHeight(1),
		m_nWidth(1),
		m_ubTextureIndex(0),
		m_type(type)
	{// 默认纹理 1 * 1 
		float white[4] = { 0.0f,0.0f ,0.0f,0.0f};
		switch (m_type)
		{
		case LM::texture_diffuse:
			m_strType = "texture_diffuse";
			white[0] = 1.0f; white[1] = 1.0f; white[2] = 1.0f; white[3] = 1.0f;
			break;
		case LM::texture_specular:
			m_strType = "texture_specular";
			white[0] = 1.0f; white[1] = 1.0f; white[2] = 1.0f; white[3] = 1.0f;
			break;
		case LM::texture_normal:
			m_strType = "texture_normal";
			white[0] = 0.5f; white[1] = 0.5f; white[2] = 1.0f;
			break;
		case LM::texture_parallax:
			m_strType = "texture_parallax";
			
			break;
		default:
			m_type = texture_unknown;
			m_strType = "texture_unknown";
			break;
		}

		glGenTextures(1, &m_uTextureID);
		glBindTexture(GL_TEXTURE_2D, m_uTextureID);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, white);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);

		
	}

	void Texture::Bind()
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + m_ubTextureIndex));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_uTextureID));
	}

	unsigned char Texture::GetIndex() const
	{
		return m_ubTextureIndex;
	}
	unsigned int Texture::GetTexID() const
	{
		return m_uTextureID;
	}
	
	const std::string& Texture::GetTexType()
	{
		// TODO: 在此处插入 return 语句
		return m_strType;
	}
	const aiString& Texture::GetTexPath()
	{
		// TODO: 在此处插入 return 语句
		return m_aistrPath;
	}
	int Texture::GetHeight() const
	{
		return m_nHeight;
	}

	int Texture::GetWidth() const
	{
		return m_nWidth;
	}
	void Texture::SetTextureWrapS(GLenum texWrap)
	{
		Bind();
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrap));
	}
	void Texture::SetTextureWrapT(GLenum texWrap)
	{
		Bind();
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texWrap));
	}
	TextureType Texture::GetTextureType() const
	{
		return m_type;
	}
	void Texture::SetTextureType(TextureType type)
	{
		m_type = type;
	}
	void Texture::SetTextureName(const std::string& texName)
	{
		m_strName = texName;
	}
	const std::string& Texture::GetTextureName() const
	{
		return m_strName;
	}
}