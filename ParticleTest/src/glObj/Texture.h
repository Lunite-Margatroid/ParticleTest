#pragma once
namespace LM
{
	// 纹理类型枚举 8bit无符号整形
	enum TextureType : uint8_t
	{
		texture_uknown,				
		texture_diffuse,	// 漫反射纹理
		texture_specular,	// 镜面反射纹理
		texture_normal,		// 法线纹理
		texture_parallax	// 视差贴图
	};

	class Texture
	{
	protected:
		unsigned int m_uTextureID;
		unsigned char m_ubTextureIndex;
		int m_nHeight;
		int m_nWidth;

		/// <summary>
		/// 纹理类型 可选texture_diffuse texture_specular texture_normal texture_height
		/// </summary>
		std::string m_strType;
		aiString m_aistrPath;		// 纹理路径

		TextureType m_type;
		/// <summary>
		/// 加载纹理
		/// </summary>
		/// <param name="texture">纹理对象id</param>
		/// <param name="path">纹理图片源文件</param>
		/// <param name="index">纹理索引</param>
		/// <param name= "texColorMode">纹理颜色模式</param>
		/// <param name= "resColorMode">源图片颜色模式</param>
		/// <param name="bGenerateMipmap">是否自动生成多级渐远纹理</param>
		/// <returns></returns>
		virtual bool LoadTexture(unsigned int* texture, const std::string& path, unsigned char index,
			int texColorMode, int resColorMode, bool bGenerateMipmap);
	public:
		

		/// <summary>
		/// 构造函数
		/// </summary>
		/// <param name="imgPath">纹理图片路径</param>
		/// <param name="index">纹理索引 从0开始，最大15</param>
		/// <param name="texColorMode">纹理的颜色模式，一般为GL_RGB或GL_RGBA。</param>
		/// <param name="imgColorMode">图片资源的颜色模式，同上</param>
		/// <param name="bGenerateMipmap">是否生成多级渐远纹理，默认为true</param>
		Texture(const std::string& imgPath, unsigned char index, int texColorMode,
			int imgColorMode, bool bGenerateMipmap = true,TextureType type = texture_diffuse);
		virtual ~Texture();
		Texture();

		virtual void Bind();
		virtual unsigned char GetIndex()const;
		unsigned int GetTexID()const;
		void InitFromModelFile(const char* filename, const std::string& directory, const std::string& type);
	
		// 迟早把这玩儿删掉
		const std::string& GetTexType();
		// 迟早把这玩儿删掉
		const aiString& GetTexPath();

		int GetHeight() const;
		int GetWidth() const;

		// 设置环绕方式
		void SetTextureWrapS(GLenum);
		// 设置环绕方式
		void SetTextureWrapT(GLenum);

		TextureType GetTextureType() const;
		void SetTextureType(TextureType type);
	};
}

