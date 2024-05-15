#include "pch.h"
#include "DirLight.h"

LM::DirLight::DirLight(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir):
	Light(ambi, diff, spec),m_v3Direction(dir)
{
}

LM::DirLight::DirLight()
{
	m_v3Direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

LM::DirLight::~DirLight()
{
}

void LM::DirLight::SetLightDirection(const glm::vec3& dir)
{
	m_v3Direction = dir;
}

void LM::DirLight::SetUniformLight(const std::string& valName, Shader& shader)
{
	Light::SetUniformLight(valName, shader);
	SetUniformDirection(valName, shader);
}

void LM::DirLight::SetUniformDirection(const std::string& valName, Shader& shader)
{
	std::string tempName = valName + ".direction";
	shader.SetUniform3f(tempName, m_v3Direction.x, m_v3Direction.y, m_v3Direction.z);
}

const glm::vec3& LM::DirLight::GetDirection() const
{
	// TODO: 在此处插入 return 语句
	return m_v3Direction;
}
