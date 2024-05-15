#include "pch.h"

#include "Shader.h"

namespace LM
{
	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{

		// ����shader����
		m_ShaderID = glCreateProgram();
		unsigned int nVertexShaderID = CompileShader(vertexShader, GL_VERTEX_SHADER);
		unsigned int nFragmentShaderID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

		AttachShader(nVertexShaderID);
		AttachShader(nFragmentShaderID);

		LinkShader();

		// ɾ����ɫ������
		GLCall(glDeleteShader(nVertexShaderID));
		GLCall(glDeleteShader(nFragmentShaderID));
	}

	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
	{
		// ����shader����
		m_ShaderID = glCreateProgram();
		unsigned int nVertexShaderID = CompileShader(vertexShader, GL_VERTEX_SHADER);
		unsigned int nFragmentShaderID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
		unsigned int nGeometryShaderID = CompileShader(geometryShader, GL_GEOMETRY_SHADER);

		AttachShader(nVertexShaderID);
		AttachShader(nFragmentShaderID);
		AttachShader(nGeometryShaderID);
		LinkShader();

		// ɾ����ɫ������
		GLCall(glDeleteShader(nVertexShaderID));
		GLCall(glDeleteShader(nFragmentShaderID));
		GLCall(glDeleteShader(nGeometryShaderID));

		// ���
		int success;
		char infoLog[512];
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
			std::cout << "ShaderProgram Error!\n" << infoLog << std::endl;
		}
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_ShaderID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_ShaderID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	unsigned int Shader::GetShaderID() const
	{
		return m_ShaderID;
	}

	void Shader::SetUniform4f(const std::string& valueName, float v1, float v2, float v3, float v4)
	{
		GLCall(glUniform4f(GetUniformLocation(valueName), v1, v2, v3, v4));
	}

	void Shader::SetUniform3f(const std::string& valueName, float v1, float v2, float v3)
	{
		GLCall(glUniform3f(GetUniformLocation(valueName), v1, v2, v3));
	}

	void Shader::SetUniform4f(const std::string& valueName, const float* v)
	{
		SetUniform4f(valueName, v[0], v[1], v[2], v[3]);
	}

	void Shader::SetUniform3f(const std::string& valueName, const float* v)
	{
		SetUniform3f(valueName, v[0], v[1], v[2]);
	}

	void Shader::SetUniform2f(const std::string& valueName, float v1, float v2)
	{
		GLCall(glUniform2f(GetUniformLocation(valueName), v1, v2));
	}
	void Shader::SetUniform2f(const std::string& valueName, const float* v)
	{
		SetUniform2f(valueName, v[0], v[1]);
	}

	void Shader::SetUniform1i(const std::string& valueName, int v1)
	{
		GLCall(glUniform1i(GetUniformLocation(valueName), v1));
	}

	void Shader::SetUniform1f(const std::string& valueName, float v1)
	{
		GLCall(glUniform1f(GetUniformLocation(valueName), v1));
	}

	void Shader::SetUniformMatrix4f(const std::string& valueName, bool transpose, const GLfloat* value)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(valueName), 1, transpose, value));
	}

	void Shader::SetUniformMatrix3f(const std::string& valueName, bool transpose, const GLfloat* value)
	{
		GLCall(glUniformMatrix3fv(GetUniformLocation(valueName), 1, transpose, value));
	}

	void Shader::SetUniformTexture(const std::string& valueName, unsigned char textureIndex)
	{
		this->SetUniform1i(valueName, textureIndex);
	}

	void Shader::SetUniformTexture(const std::string& varName, unsigned int textureID, unsigned char textureIndex)
	{
		glActiveTexture(GL_TEXTURE0 + textureIndex);
		glBindTexture(GL_TEXTURE_2D, textureID);
		this->SetUniform1i(varName, textureIndex);
	}

	void Shader::SetUniformTextureCube(const std::string& valueName, unsigned char textureIndex)
	{
		this->SetUniform1i(valueName, textureIndex);
	}

	void Shader::UniformBlockBinding(const char* blockName, unsigned int index)
	{
		// Bind();
		unsigned int uniformIndex;
		GLCall(uniformIndex = glGetUniformBlockIndex(m_ShaderID, blockName));
		GLCall(glUniformBlockBinding(m_ShaderID , uniformIndex, index));
	}

	unsigned int Shader::GetUniformBlockIndex(const char* uniformBlockName)
	{
		unsigned int uniformIndex;
		GLCall(uniformIndex = glGetUniformBlockIndex(m_ShaderID, uniformBlockName));
		return uniformIndex;
	}


	int Shader::GetUniformLocation(const std::string& valueName)
	{
		if (m_UniformMapLocation.find(valueName) != m_UniformMapLocation.end())
			return m_UniformMapLocation[valueName];
		int location = -1;
		GLCall(location = glGetUniformLocation(m_ShaderID, valueName.c_str()));
		if (location == -1)
		{
			std::cout << "Can't find uniform value '" << valueName << "' !" << std::endl;
		}
		m_UniformMapLocation[valueName] = location;
		return location;
	}

	

	void Shader::GetShaderSource(const std::string& path, std::string& shaderSource)
	{
		std::ifstream infile;
		std::stringstream sstr;
		infile.open(path, std::ios::in);
		if (infile)
		{
			while (!infile.eof())
			{
				std::string str_t;
				getline(infile, str_t);
				sstr << str_t << '\n';
			}
		}
		else
		{
			std::cout << "Can't open file" << "\" " << path << "\" !" << std::endl;
			infile.close();
			__debugbreak();
			return;
		}

		shaderSource = sstr.str();
		infile.close();
		return;
	}
	unsigned int Shader::CompileShader(const std::string& path, GLenum typeShader)
	{
		unsigned int nShaderID;
		std::string strType;
		switch (typeShader)
		{
		case GL_VERTEX_SHADER:
			strType = "Vertex Shader"; break;
		case GL_FRAGMENT_SHADER:
			strType = "Fragment Shader"; break;
		case GL_GEOMETRY_SHADER:
			strType = "Geometry Shader"; break;
		default:
			strType = "[ERROR] Unkonwn Type Shader"; break;
		}
		GLCall(nShaderID = glCreateShader(typeShader));
		std::string strShaderSource;
		GetShaderSource(path, strShaderSource);

		// ------compile--------
		int success;
		char infoLog[512];
		const char* strSource = strShaderSource.c_str();
		GLCall(glShaderSource(nShaderID, 1, &strSource, NULL));
		glCompileShader(nShaderID);
		// ------check----------
		glGetShaderiv(nShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(nShaderID, 512, NULL, infoLog);
			std::cout << strType << " compile error!\n" << infoLog << std::endl;
		}

		return nShaderID;
	}
	void Shader::AttachShader(unsigned int nShaderID)
	{
		GLCall(glAttachShader(m_ShaderID, nShaderID));
	}
	void Shader::LinkShader()
	{
		GLCall(glLinkProgram(m_ShaderID));
	}
}