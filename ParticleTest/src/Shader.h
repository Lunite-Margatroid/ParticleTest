#pragma once
namespace LM
{
	class Shader
	{
	private:
		unsigned int m_ShaderID;
		std::unordered_map<std::string, int> m_UniformMapLocation;
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
		
		~Shader();

		void Bind() const;
		void Unbind() const;



		int GetUniformLocation(const std::string& valueName);


		void SetUniform4f(const std::string& valueName, float v1, float v2, float v3, float v4);
		void SetUniform3f(const std::string& valueName, float v1, float v2, float v3);
		void SetUniform1i(const std::string& valueName, int v1);
		void SetUniform1f(const std::string& valueName, float v1);
		/// <summary>
		/// ���� 4x4 float ����
		/// </summary>
		/// <param name="valueName">������</param>
		/// <param name="transpose">�Ƿ�ת��</param>
		/// <param name="value">����ָ��</param>
		void SetUniformMatrix4f(const std::string& valueName, bool transpose, const GLfloat* value);

		void SetUniformMatrix3f(const std::string& valueName, bool transpose, const GLfloat* value);
		
		/// <summary>
		/// �Ƽ�ʹ���������
		/// </summary>
		/// <param name="valueName"> �������� </param>
		/// <param name="textureIndex"> ����slot������ </param>
		void SetUniformTexture(const std::string& valueName, unsigned char textureIndex);
		/// <summary>
		/// �Ƽ�ʹ���������
		/// </summary>
		/// <param name="valueName"> �������� </param>
		/// <param name="textureID"> ��������id </param>
		/// <param name="textureIndex"> ����slot������ </param>
		void SetUniformTexture(const std::string& valueName, unsigned int textureID, unsigned char textureIndex);

		void SetUniformTextureCube(const std::string& valueName, unsigned char textureIndex);
		/// <summary>
		/// ��Uniform�鵽�󶨵�
		/// </summary>
		/// <param name="blockName">Uniform������</param>
		/// <param name="index">�󶨵���</param>
		void UniformBlockBinding(const char* blockName, unsigned int index);

		void SetUniformModelTrans(glm::mat4&);
		void SetUniformViewTrans(glm::mat4&);
		void SetUniformProjectionTrans(glm::mat4&);
		void SetUniformNormalMat(glm::mat3&);
		void SetUniformCameraPos(glm::vec3&);
	private:
		
		static void GetShaderSource(const std::string& path, std::string& shaderCode);
		static unsigned int CompileShader(const std::string& path, GLenum typeShader);
		void AttachShader(unsigned int nShaderID);
		void LinkShader();
	};
}