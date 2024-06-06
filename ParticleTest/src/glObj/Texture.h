#pragma once
namespace LM
{
	// ��������ö�� 8bit�޷�������
	enum TextureType : uint8_t
	{
		texture_unknown,				
		texture_diffuse,	// ����������
		texture_specular,	// ���淴������
		texture_normal,		// ��������
		texture_parallax	// �Ӳ���ͼ
	};

	class Texture
	{
	protected:
		unsigned int m_uTextureID;
		unsigned char m_ubTextureIndex;
		int m_nHeight;
		int m_nWidth;

		/// <summary>
		/// �������� ��ѡtexture_diffuse texture_specular texture_normal texture_height
		/// </summary>
		std::string m_strType;
		std::string m_strName;
		aiString m_aistrPath;		// ����·��

		TextureType m_type;
		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="texture">�������id</param>
		/// <param name="path">����ͼƬԴ�ļ�</param>
		/// <param name="index">��������</param>
		/// <param name= "texColorMode">������ɫģʽ</param>
		/// <param name= "resColorMode">ԴͼƬ��ɫģʽ</param>
		/// <param name="bGenerateMipmap">�Ƿ��Զ����ɶ༶��Զ����</param>
		/// <returns></returns>
		virtual bool LoadTexture(unsigned int* texture, const std::string& path, unsigned char index,
			int texColorMode, int resColorMode, bool bGenerateMipmap, bool yReverse);
	public:

		Texture(const std::string& imgPath, TextureType type = texture_diffuse, GLenum dstColorMode = GL_RGB, GLenum srcColorMode = GL_RGB,
			GLenum minFilter = GL_NEAREST_MIPMAP_LINEAR, GLenum magFilter = GL_LINEAR, GLenum wrap = GL_REPEAT, bool yReverse = true);
		virtual ~Texture();
		Texture(TextureType type = texture_diffuse);

		virtual void Bind();
		virtual unsigned char GetIndex()const;
		unsigned int GetTexID()const;
		void InitFromModelFile(const char* filename, const std::string& directory, const std::string& type);
	

		const std::string& GetTexType();
		// ����������ɾ��
		const aiString& GetTexPath();

		int GetHeight() const;
		int GetWidth() const;

		// ���û��Ʒ�ʽ
		void SetTextureWrapS(GLenum);
		// ���û��Ʒ�ʽ
		void SetTextureWrapT(GLenum);

		TextureType GetTextureType() const;
		void SetTextureType(TextureType type);

		void SetTextureName(const std::string& texName);
		const std::string& GetTextureName()const;

	};
}

