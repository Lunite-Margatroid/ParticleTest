#include "pch.h"
#include "SkyboxSprite.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	void SkyboxSprite::Init()
	{
		m_vao = Renderer::GetVertexArray(Renderer::VertexArrays::Cube_P_N_T_TG);

		m_ShaderName = LM::Shaders::Skybox_P;
		m_Transparency = false;
		m_Visible = true;


	}
	void SkyboxSprite::Render(const glm::mat4& modelTrans)
	{
	}
	void SkyboxSprite::RenderSkybox()
	{
	}
}