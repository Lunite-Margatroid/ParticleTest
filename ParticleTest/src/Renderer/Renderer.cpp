#include "pch.h"
#include "Renderer.h"

namespace ptt
{
	Renderer* Renderer::s_Instance = nullptr;

	Renderer::Renderer():
		m_ViewTrans(1.0f),
		m_ModelTrans(1.0f),
		m_ProjectionTrans(1.0f),
		m_CurrentShader(nullptr),
		m_CurrentCamera(nullptr)
	{
	}
	Renderer::~Renderer()
	{
	}
	void Renderer::SetTransMat()
	{
	}
	void Renderer::SetViewTrans(const glm::mat4& viewTrans)
	{
	}
	void Renderer::SetModelTrans(const glm::mat4& modelTrans)
	{
	}
	void Renderer::SetProjectionTrans(const glm::mat4& projectionTrans)
	{
	}
	Renderer* Renderer::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Renderer();
			return s_Instance;
		}
		return s_Instance;
	}
	LM::Shader* Renderer::GetCurrentShader()
	{
		return GetInstance()->m_CurrentShader;
	}
}