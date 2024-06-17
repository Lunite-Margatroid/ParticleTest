#include "pch.h"
#include "SkyboxSprite.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	void SkyboxSprite::Init()
	{
		m_vao = Renderer::GetVertexArray(Renderer::VertexArrays::Cube_P_N_T_TG);

		m_ShaderName = LM::Shaders::Skybox_P;
		m_Shader = Renderer::GetShader(m_ShaderName);
		m_Transparency = false;
		m_Visible = true;

		m_CubeTexture.LoadTexture("./res/img/right.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		m_CubeTexture.LoadTexture("./res/img/left.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		m_CubeTexture.LoadTexture("./res/img/top.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		m_CubeTexture.LoadTexture("./res/img/bottom.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		m_CubeTexture.LoadTexture("./res/img/front.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		m_CubeTexture.LoadTexture("./res/img/back.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	}
	SkyboxSprite::SkyboxSprite()
	{
		Init();
	}
	void SkyboxSprite::Render(const glm::mat4& modelTrans)
	{
		Renderer::PushSkyboxSprite(this);
	}
	void SkyboxSprite::RenderSkybox()
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;
		const glm::mat4 &viewTrans = camera->GetViewTrans();
		const glm::mat4& projectionTrans = camera->GetProjectionTrans();
		m_Shader->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexture.GetTexID());
		m_Shader->SetUniformTextureCube("u_CubeMap", 0);
		m_Shader->SetUniformMatrix4f("u_ViewTrans", false, glm::value_ptr(viewTrans));
		m_Shader->SetUniformMatrix4f("u_ProjectionTrans", false, glm::value_ptr(projectionTrans));
		m_vao->DrawElement();
	}
}