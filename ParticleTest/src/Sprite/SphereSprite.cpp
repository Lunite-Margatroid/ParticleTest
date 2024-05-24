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
		if (init)
			Init();
	}
	SphereSprite::SphereSprite()
		:CubeSprite(false)
	{
		Init();
	}
	void SphereSprite::SelectShader()
	{
		if (m_Lighted)
		{
			m_Shader = Renderer::GetShader(Renderer::Shaders::LightedMesh_Sphere_P_T_TG);
			LightedDemoScene* scene = dynamic_cast<LightedDemoScene*>(Application::GetCurrentScene());
			if (scene)
				scene->BindLightBuffer();
		}
		else
			m_Shader = Renderer::GetShader(Renderer::Shaders::Mesh_Sphere_P_T_TG);
	}
}