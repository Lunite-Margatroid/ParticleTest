#include "pch.h"
#include "SphereSprite.h"
#include "demoscene/LightedDemoScene.h"
#include "Application.h"
namespace ptt
{
	void SphereSprite::Init()
	{
		m_vao = Renderer::GetVertexArray(Renderer::VertexArrays::Sphere_P_T_TG);
		m_Lighted = false;
	}
	SphereSprite::SphereSprite(bool init)
		:CubeSprite(false)
	{
		m_ShaderName = LM::Shaders::Mesh_Sphere_P_T_TG;
		if (init)
			Init();
	}
	SphereSprite::SphereSprite()
		:CubeSprite(false)
	{
		m_ShaderName = LM::Shaders::Mesh_Sphere_P_T_TG;
		Init();
	}
	void SphereSprite::SelectShader()
	{
		Sprite::SelectShader();
	}
}