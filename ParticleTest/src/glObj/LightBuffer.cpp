#include "pch.h"
#include "LightBuffer.h"

namespace ptt
{
	LightBuffer::LightBuffer(int count, LM::Light* lights, LM::LightType lightType)
		:m_Count(count), m_LightType(lightType), m_MaxSize(1024)
	{
		GLCall(glGenBuffers(1, &m_Buffer));
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_MaxSize, NULL, GL_DYNAMIC_DRAW);

		Init(count, lights);
	}
	LightBuffer::LightBuffer()
		:m_Count(0), m_MaxSize(1024)
	{
		GLCall(glGenBuffers(1, &m_Buffer));
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_MaxSize, NULL, GL_DYNAMIC_DRAW);

		Init(0, nullptr);
	}
	LightBuffer::~LightBuffer()
	{
		glDeleteBuffers(1, &m_Buffer);
	}
	void LightBuffer::Init(int count, LM::Light* lights)
	{
		unsigned int offset = 0;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffer);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(int), &m_Count);
		offset += 4 * sizeof(float);

		for (int i = 0; i < count; i++)
		{
			offset = lights[i].WriteBuffer(GL_SHADER_STORAGE_BUFFER, offset);
			ASSERT(offset < m_MaxSize);
		}
	}
	void LightBuffer::BindToShaderStorage(LM::Shader* shader, const std::string& bufferName)
	{
		/*
			layout(std140£¬ binding = 0)buffer DirLights
			{
				int countDirLight;
				struct DirLight dataDirLights[];
			};

			layout(std140,binding = 1)buffer PointLights
			{
				int countPointLight;
				struct PointLight dataPointLights[];
			};

			layout(std140, binding = 2)buffer SpotLights
			{
				int countSpotLight;
				struct SpotLight dataSpotLights[];
			};
		*/
		unsigned int bindingNode;
		switch (m_LightType)
		{
		case LM::LightType::DirectionLight: bindingNode = 0; break;
		case LM::LightType::PointLight: bindingNode = 1; break;
		case LM::LightType::SpotLight: bindingNode = 2; break;
		default:bindingNode = 3; break;
		}
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingNode, m_Buffer);
	}
}