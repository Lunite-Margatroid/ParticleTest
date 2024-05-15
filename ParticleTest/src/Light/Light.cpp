#include "pch.h"
#include "Light.h"

void LM::Light::SetUniformLight(const std::string& valueName, Shader& shader)
{
	std::string tempName = valueName + ".ambient";
	shader.SetUniform3f(tempName, m_v3Ambient.x, m_v3Ambient.y, m_v3Ambient.z);

	tempName = valueName + ".diffuse";
	shader.SetUniform3f(tempName, m_v3Diffuse.x, m_v3Diffuse.y, m_v3Diffuse.z);

	tempName = valueName + ".specular";
	shader.SetUniform3f(tempName, m_v3Specular.x, m_v3Specular.y, m_v3Specular.z);
}

void LM::Light::SetLightColor(const glm::vec3& ambi, const glm::vec3& diff, const glm::vec3& spec)
{
	m_v3Ambient = ambi;
	m_v3Diffuse = diff;
	m_v3Specular = spec;
}

LM::Light::Light(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec):
	m_v3Ambient(ambi),m_v3Diffuse(diff),m_v3Specular(spec)
{

}

LM::Light::Light()
{
	m_v3Ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	m_v3Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	m_v3Specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

LM::Light::~Light()
{
}

glm::vec3 LM::Light::GetAmbient() const
{
	return m_v3Ambient;
}

glm::vec3 LM::Light::GetDiffuse() const
{
	return m_v3Diffuse;
}

glm::vec3 LM::Light::GetSpecular() const
{
	return m_v3Specular;
}
