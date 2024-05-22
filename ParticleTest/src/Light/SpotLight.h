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
		float m_fInnerBdr;
		float m_fOuterBdr;
		

		float m_radInnerBdr;
		float m_radOuterBdr;
		
	public:
		SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position,glm::vec3 direction, LightType type = LightType::SpotLight);
		SpotLight();
		~SpotLight();
		void SetUniformLight(const std::string& valName, Shader&shader);

		/// <summary>
		/// ����߽�Ƕ� ������
		/// </summary>
		/// <param name="outer"></param>
		/// <param name="inner"></param>
		void SetLightBoundary(float outer, float inner);
		unsigned int WriteBuffer(GLenum target, unsigned int offset) override;

		virtual void LightEditor() override;
	};
}