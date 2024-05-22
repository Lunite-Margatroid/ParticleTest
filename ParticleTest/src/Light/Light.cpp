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

LM::Light::Light(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec, LightType type) :
	m_v3Ambient(ambi), m_v3Diffuse(diff), m_v3Specular(spec), m_Type(type), m_Lighted(true)
{

}

LM::Light::Light()
	:m_v3Ambient(0.3f, 0.3f, 0.3f),
	m_v3Diffuse(0.8f, 0.8f, 0.8f),
	m_v3Specular(1.0f, 1.0f, 1.0f),
	m_Type(LightType::UnknownLight),
	m_Lighted(true)
{

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

void LM::Light::LightEditor()
{
	ImGui::SeparatorText("Light Editor");
	ImGui::Checkbox("Enable", &m_Lighted);
	ImGui::ColorEdit3("Ambient", &m_v3Ambient.r);
	ImGui::ColorEdit3("Diffuse", &m_v3Diffuse.r);
	ImGui::ColorEdit3("Specular", &m_v3Specular.r);
}

bool LM::Light::IsLighted() const
{
	return m_Lighted;
}

void LM::Light::SetLighted(bool ifLight)
{
	m_Lighted = ifLight;
}

LM::LightType LM::Light::GetLightType() const
{
	return m_Type;
}
