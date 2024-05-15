#include "pch.h"
#include "PointLight.h"

LM::PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position):
	Light(ambient, diffuse, specular),m_v3Position(position)
{
	m_kConstant = 1.0f;
	m_kLinear = 0.1f;
	m_kQuadratic = 0.01f;
}

LM::PointLight::PointLight()
{
	m_v3Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_kConstant = 1.0f;
	m_kLinear = 0.1f;
	m_kQuadratic = 0.01f;
}

LM::PointLight::~PointLight()
{
}

void LM::PointLight::SetUniformLight(const std::string& valName, Shader& shader)
{
	Light::SetUniformLight(valName, shader);
	std::string tempName = valName + ".position";
	shader.SetUniform3f(tempName, m_v3Position.x, m_v3Position.y, m_v3Position.z);

	tempName = valName + ".kConstant";
	shader.SetUniform1f(tempName, m_kConstant);

	tempName = valName + ".kLinear";
	shader.SetUniform1f(tempName, m_kLinear);

	tempName = valName + ".kQuadratic";
	shader.SetUniform1f(tempName, m_kQuadratic);
}

void LM::PointLight::SetUniformPosition(const std::string& valName, Shader& shader)
{
	std::string tempName = valName + ".position";
	shader.SetUniform3f(tempName, m_v3Position.x, m_v3Position.y, m_v3Position.z);
}

void LM::PointLight::SetLightPosition(const glm::vec3& position)
{
	m_v3Position = position;
}

void LM::PointLight::SetLightAttenuation(float constant, float linear, float quadratic)
{
	m_kConstant = constant;
	m_kLinear = linear;
	m_kQuadratic = quadratic;
}

glm::vec3 LM::PointLight::GetLightPosition() const
{
	return m_v3Position;
}

float LM::PointLight::GetKConstant() const
{
	return m_kConstant;
}

float LM::PointLight::GetKLinear() const
{
	return m_kLinear;
}

float LM::PointLight::GetKQuadratic() const
{
	return m_kQuadratic;
}
