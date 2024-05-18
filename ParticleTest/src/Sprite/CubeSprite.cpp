#include "pch.h"
#include "CubeSprite.h"

namespace ptt
{
	void CubeSprite::Init()
	{
		m_vao = Renderer::GetVertexArray(Renderer::VertexArrays::Cube_V_N_T);
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
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::Mesh_V_N_T);
		if (shader == nullptr)
			return;

		LM::Texture* tex = m_Textures[0].m_Texture;
		tex->Bind();
		shader->Bind();
		shader->SetUniformTexture("u_Tex", tex->GetIndex());
		shader->SetUniform2f("u_TexOffset", m_Textures[0].offsetx, m_Textures[0].offsety);
		shader->SetUniform2f("u_TexScale", m_Textures[0].scalex, m_Textures[0].scaley);

		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		glm::mat3& normalTrans = Renderer::GetNormalTrans();
		glm::mat4& mvTrans = Renderer::GetMVTrans();
		mvTrans = camera->GetViewTrans() * modelTrans;
		mvpTrans = camera->GetProjectionTrans() * mvTrans;
		normalTrans = glm::transpose(glm::inverse(glm::mat3(modelTrans)));
		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));
		shader->SetUniformMatrix3f("u_NormalTrans", false, glm::value_ptr(normalTrans));
		shader->SetUniformMatrix4f("u_VTrans", false, glm::value_ptr(camera->GetViewTrans()));
		shader->SetUniform4f("u_Color", &m_Color[0].r);

		m_vao->DrawElement();
	}
}