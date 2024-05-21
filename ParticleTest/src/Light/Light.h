#pragma once
#include "Shader/Shader.h"
namespace LM
{
	enum class LightType
	{
		UnknownLight,
		DirectionLight, PointLight, SpotLight
		
	};

	class Light
	{

	protected:
		glm::vec3 m_v3Ambient;		// 环境光
		glm::vec3 m_v3Diffuse;		// 漫反射
		glm::vec3 m_v3Specular;		// 镜面反射

		LightType m_Type;
		bool m_Lighted;

	public:
		virtual void SetUniformLight(const std::string& valueName, Shader& shader);
		void SetLightColor(const glm::vec3& ambi, const glm::vec3& diff, const glm::vec3& spec);
		Light(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec, LightType type);
		Light();
		virtual ~Light();

		glm::vec3 GetAmbient() const;
		glm::vec3 GetDiffuse() const;
		glm::vec3 GetSpecular() const;

		virtual unsigned int WriteBuffer(GLenum target, unsigned int offset) = 0;
		virtual void LightEditor();
		bool IsLighted() const;
		void SetLighted(bool ifLight);

		LightType GetLightType() const;
	};
}