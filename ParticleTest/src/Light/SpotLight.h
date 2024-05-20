#pragma once
#include "PointLight.h"
#include "DirLight.h"
namespace LM
{
	class SpotLight :
		public DirLight, public PointLight
	{
		/*
			说明
			对应着色器内结构
			 聚光
			struct SpotLight
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				
				vec3 position;
				vec3 direction;
				
				// 衰减
				float kConstant;		// 常数项
				float kLinear;			// 一次项
				float kQuadratic;		// 2次项

				float innerbdr;			// 内边界的cos
				float outerbdr;			// 外边界的cos
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

		/// <summary>
		/// 输入边界角度 弧度制
		/// </summary>
		/// <param name="outer"></param>
		/// <param name="inner"></param>
		void SetLightBoundary(float outer, float inner);
	};
}