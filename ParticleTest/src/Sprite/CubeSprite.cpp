#include "pch.h"
#include "CubeSprite.h"
#include "Application.h"
#include "demoscene/LightedDemoScene.h"

namespace ptt
{
	void CubeSprite::Init()
	{
		m_vao = Renderer::GetVertexArray(Renderer::VertexArrays::Cube_P_N_T_TG);
	}
	CubeSprite::CubeSprite(bool init)
		:QuadSprite(false)
	{
		if (init)
			Init();
	}

	void CubeSprite::Render(const glm::mat4& modelTrans)
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;
		SelectShader();

		m_Shader->Bind();
		SetUniformMaterial(m_Shader);

		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		glm::mat3& normalTrans = Renderer::GetNormalTrans();
		glm::mat4& mvTrans = Renderer::GetMVTrans();
		mvTrans = camera->GetViewTrans() * modelTrans;
		mvpTrans = camera->GetProjectionTrans() * mvTrans;
		normalTrans = glm::transpose(glm::inverse(glm::mat3(modelTrans)));
		m_Shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));
		m_Shader->SetUniformMatrix3f("u_NormalTrans", false, glm::value_ptr(normalTrans));
		m_Shader->SetUniformMatrix4f("u_VTrans", false, glm::value_ptr(camera->GetViewTrans()));
		m_Shader->SetUniformMatrix4f("u_MTrans", false, glm::value_ptr(modelTrans));
		m_Shader->SetUniform4f("u_Color", &m_Color[0].r);
		m_Shader->SetUniform3f("u_CameraPos", &(camera->GetPosition().x));

		m_vao->DrawElement();
	}
}