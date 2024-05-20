#include "pch.h"
#include "SpotLight.h"

LM::SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction) :
	Light(ambient,diffuse,specular)
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
