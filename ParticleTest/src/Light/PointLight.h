#pragma once
#include "Light.h"
namespace LM
{
	class PointLight :
		virtual public Light
	{
		/*
		˵��
		��Ӧ��ɫ���ṹ
			struct PointLight
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;

				vec3 position;
				// ˥��
				float kConstant;		// ������
				float kLinear;			// һ����
				float kQuadratic;		// 2����
			};
		
		*/
	protected:
		glm::vec3 m_v3Position;
	
		// ˥��
		float m_kConstant;		// ������
		float m_kLinear;			// һ����
		float m_kQuadratic;		// 2����
	public:
		PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
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
	};

}