#pragma once
#include "Light.h"
namespace LM
{
	class PointLight :
		virtual public Light
	{
		/*
		说明
		对应着色器结构
			struct PointLight
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;

				vec3 position;
				// 衰减
				float kConstant;		// 常数项
				float kLinear;			// 一次项
				float kQuadratic;		// 2次项
			};
		
		*/
	protected:
		glm::vec3 m_v3Position;

		// 衰减
		float m_kConstant;		// 常数项
		float m_kLinear;			// 一次项
		float m_kQuadratic;		// 2次项
	public:
		PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, LightType type = LightType::PointLight);
		PointLight();
		virtual ~PointLight();
		void SetUniformLight(const std::string& valName, Shader& shader);
		void SetUniformPosition(const std::string& valName, Shader& shader);
		void SetLightPosition(const glm::vec3& position);
		void SetLightAttenuation(float constant, float linear, float quadratic);

		glm::vec3 GetLightPosition() const;

		float GetKConstant() const;
		float GetKLinear() const;
		float GetKQuadratic() const;

		unsigned int WriteBuffer(GLenum target, unsigned int offset) override;
		virtual void LightEditor() override;
	};

}