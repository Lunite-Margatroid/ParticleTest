#include "pch.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Texture.h"
#include <wchar.h>
#include <codecvt>
namespace LM
{

	bool Texture::LoadTexture(unsigned int* texture, const std::string& path, unsigned char index, int texColorMode, int resColorMode, bool bGenerateMipmap)
	{
		int nChannals;
		unsigned char* img_data;
		stbi_set_flip_vertically_on_load(true);	// ��תy��
		// ԭ�㵽��ͼƬ�����½�


		img_data = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &nChannals, 0);

		if (img_data == 0)
		{
			std::cout << "Fail to load img!----" << path << std::endl;
			return false;
		}
		GLCall(glGenTextures(1, texture));
		GLCall(glActiveTexture(GL_TEXTURE0 + index));
		GLCall(glBindTexture(GL_TEXTURE_2D, *texture)); // ������

		if (nChannals == 4)
			resColorMode = GL_RGBA;
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texColorMode, m_nWidth, m_nHeight, 0, resColorMode, GL_UNSIGNED_BYTE, img_data));
		// param1 ����Target
		// param2 �༶��Զ���� 0Ϊ��������
		// param3 �����ʽ
		// param4&5 ��Ⱥ͸߶�x&y
		// param6 ��ʷ���� ��Ϊ0
		// param7 Դ���ݸ�ʽ
		// param8 Դ��������
		// param9 Դ����

		if (bGenerateMipmap)
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// �Զ����ɶ༶��Զ��������
		stbi_image_free(img_data);						// �ͷ�ͼ����Դ
		return true;
	}

	Texture::Texture(const std::string& imgPath, TextureType type, GLenum dstColorMode, GLenum srcColorMode, GLenum minFilter, GLenum magFilter, GLenum wrap)
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
		this->LoadTexture(&m_uTextureID, imgPath, 0, dstColorMode, srcColorMode, ifMipmap);
		m_ubTextureIndex = 0;
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));		// ���û��Ʒ�ʽ

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter));	// ���ò�ֵ��ʽ
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
	{// Ĭ������ 1 * 1 
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
		// TODO: �ڴ˴����� return ���
		return m_strType;
	}
	const aiString& Texture::GetTexPath()
	{
		// TODO: �ڴ˴����� return ���
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