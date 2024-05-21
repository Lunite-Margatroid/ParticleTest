#include "pch.h"
#include "DirLight.h"

LM::DirLight::DirLight(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir, LightType type):
	Light(ambi, diff, spec, type),m_v3Direction(dir)
{
}

LM::DirLight::DirLight()
{
	m_v3Direction = glm::vec3(0.0f, -1.0f, 0.0f);
	m_Type = LightType::DirectionLight;

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

unsigned int LM::DirLight::WriteBuffer(GLenum target, unsigned int offset)
{
	/*
	struct DirLight
	{
		vec3 ambient;			// 环境光
		vec3 diffuse;			// 漫反射
		vec3 specular;			// 镜面反射

		vec3 direction;			// 光照方向
	};
	*/
	if (m_Lighted)
	{// lighted
		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Ambient.r);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Diffuse.r);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Specular.r);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Direction.x);
		offset += 4 * sizeof(float);
	}
	else
	{// unlighted
		float unlighted[3] = {0.0f, 0.0f, 0.0f};
		glBufferSubData(target, offset, 3 * sizeof(float), unlighted);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), unlighted);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), unlighted);
		offset += 4 * sizeof(float);

		glBufferSubData(target, offset, 3 * sizeof(float), &m_v3Direction.x);
		offset += 4 * sizeof(float);
	}

	return offset;
}
