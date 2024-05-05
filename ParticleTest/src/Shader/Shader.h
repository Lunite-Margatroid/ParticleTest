#pragma once
namespace LM
{
	class Shader
	{
	protected:
		unsigned int m_ShaderID;
		std::unordered_map<std::string, int> m_UniformMapLocation;
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
		
		virtual ~Shader();

		void Bind() const;
		void Unbind() const;

		unsigned int GetShaderID()const;


		int GetUniformLocation(const std::string& valueName);


		void SetUniform4f(const std::string& valueName, float v1, float v2, float v3, float v4);
		void SetUniform3f(const std::string& valueName, float v1, float v2, float v3);
		void SetUniform4f(const std::string& valueName, const float* v);
		void SetUniform3f(const std::string& valueName, const float* v);
		void SetUniform1i(const std::string& valueName, int v1);
		void SetUniform1f(const std::string& valueName, float v1);
		/// <summary>
		/// 设置 4x4 float 矩阵
		/// </summary>
		/// <param name="valueName">变量名</param>
		/// <param name="transpose">是否转置</param>
		/// <param name="value">数据指针</param>
		void SetUniformMatrix4f(const std::string& valueName, bool transpose, const GLfloat* value);

		void SetUniformMatrix3f(const std::string& valueName, bool transpose, const GLfloat* value);
		
		/// <summary>
		/// 推荐使用这个重载
		/// </summary>
		/// <param name="valueName"> 变量名称 </param>
		/// <param name="textureIndex"> 纹理slot的索引 </param>
		void SetUniformTexture(const std::string& valueName, unsigned char textureIndex);
		/// <summary>
		/// 推荐使用这个重载
		/// </summary>
		/// <param name="valueName"> 变量名称 </param>
		/// <param name="textureID"> 纹理对象的id </param>
		/// <param name="textureIndex"> 纹理slot的索引 </param>
		void SetUniformTexture(const std::string& valueName, unsigned int textureID, unsigned char textureIndex);

		void SetUniformTextureCube(const std::string& valueName, unsigned char textureIndex);
		/// <summary>
		/// 绑定Uniform块到绑定点
		/// </summary>
		/// <param name="blockName">Uniform块命名</param>
		/// <param name="index">绑定点编号</param>
		void UniformBlockBinding(const char* blockName, unsigned int index);

		unsigned int GetUniformBlockIndex(const char* uniformBlockName);
	protected:
		
		static void GetShaderSource(const std::string& path, std::string& shaderCode);
		static unsigned int CompileShader(const std::string& path, GLenum typeShader);
		void AttachShader(unsigned int nShaderID);
		void LinkShader();
	};
}