#include "pch.h"
#include "SpotLight.h"

LM::SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, LightType type)
	:
	Light(ambient,diffuse,specular, type)
{
	m_v3Position = position;
	m_v3Direction = direction;
	m_fInnerBdr = cos(3.14159f / 12.f);
	m_fOuterBdr = cos(3.14159f / 10.f);
}

LM::SpotLight::SpotLight()
{
	m_fInnerBdr = cos(3.14159f / 16.f);
	m_fOuterBdr = cos(3.14159f / 10.f);
	m_Type = LightType::SpotLight;
}

LM::SpotLight::~SpotLight()
{
}

void LM::SpotLight::SetUniformLight(const std::string& valName, Shader& shader)
{
	PointLight::SetUniformLight(valName, shader);

	std::string tempName = valName + ".direction";
	shader.SetUniform3f(tempName, m_v3Direction.x, m_v3Direction.y, m_v3Direction.z);

	tempName = valName + ".innerbdr";
	shader.SetUniform1f(tempName, m_fInnerBdr);

	tempName = valName + ".outerbdr";
	shader.SetUniform1f(tempName, m_fOuterBdr);

}

void LM::SpotLight::SetLightBoundary(float outer, float inner)
{
	if (inner > outer)
	{
		m_fOuterBdr = cosf(inner);
		m_fInnerBdr = cosf(outer);
	}
	else
	{
		m_fOuterBdr = cosf(outer);
		m_fInnerBdr = cosf(inner);
	}
}

unsigned int LM::SpotLight::WriteBuffer(GLenum target, unsigned int offset)
{
	/*
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
	if (m_Lighted)
	{
		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Ambient.r);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Diffuse.r);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Specular.r);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Position.x);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Direction.x);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 5 * sizeof(float), &m_kConstant);
		offset += 8 * sizeof(float);
	}
	else
	{
		float unlighted[3] = {0.0f,0.0f,0.0f};
		glBufferSubData(target, offset, 3 * sizeof(float), unlighted);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), unlighted);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), unlighted);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Position.x);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Direction.x);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 5 * sizeof(float), &m_kConstant);
		offset += 8 * sizeof(float);
	}
	return offset;
}
