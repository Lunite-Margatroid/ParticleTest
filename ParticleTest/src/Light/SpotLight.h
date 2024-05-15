#pragma once
#include "PointLight.h"
#include "DirLight.h"
namespace LM
{
	class SpotLight :
		public DirLight, public PointLight
	{
		/*
			˵��
			��Ӧ��ɫ���ڽṹ
			 �۹�
			struct SpotLight
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				
				vec3 position;
				vec3 direction;
				
				// ˥��
				float kConstant;		// ������
				float kLinear;			// һ����
				float kQuadratic;		// 2����

				float innerbdr;			// �ڱ߽��cos
				float outerbdr;			// ��߽��cos
				// innerbdr > outerbdr
			};
		*/
	protected:
		float m_fOuterBdr;
		float m_fInnerBdr;
	public:
		SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position,glm::vec3 direction);
		SpotLight();
		~SpotLight();
		void SetUniformLight(const std::string& valName, Shader&shader);
		void SetLightBoundary(float outer, float inner);
	};
}