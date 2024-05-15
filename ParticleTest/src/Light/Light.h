#pragma once
#include "Shader/Shader.h"

namespace LM
{
	class Light
	{
	protected:
		glm::vec3 m_v3Ambient;		// 环境光
		glm::vec3 m_v3Diffuse;		// 漫反射
		glm::vec3 m_v3Specular;		// 镜面反射
	public:
		virtual void SetUniformLight(const std::string& valueName, Shader& shader);
		void SetLightColor(const glm::vec3& ambi, const glm::vec3& diff, const glm::vec3& spec);
		Light(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec);
		Light();
		virtual ~Light();

		glm::vec3 GetAmbient() const;
		glm::vec3 GetDiffuse() const;
		glm::vec3 GetSpecular() const;
	};
}