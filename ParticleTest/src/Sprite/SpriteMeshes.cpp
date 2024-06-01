#include "pch.h"
#include "SpriteMeshes.h"
#include "Application.h"
#include "demoscene/LightedDemoScene.h"
namespace ptt
{
	SpriteMeshes::SpriteMeshes()
	{
	}
	void SpriteMeshes::PushMeshBack(Mesh* mesh)
	{
		m_Meshes.push_back(mesh);
	}
	void SpriteMeshes::Render(const glm::mat4& modelTrans)
	{
		if (m_Meshes.size() == 0)
			return;
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;
		SelectShader();
		if (m_Shader == nullptr)
			return;
		m_Shader->Bind();

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

		for (int i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i]->Render(m_Shader);
		}
	}
	void SpriteMeshes::SelectShader()
	{
		if (m_Lighted)
		{
			m_Shader = Renderer::GetShader(Renderer::Shaders::LightedMesh_P_N_T_TG);
			LightedDemoScene* scene = dynamic_cast<LightedDemoScene*>(Application::GetCurrentScene());
			if (scene)
				scene->BindLightBuffer();
		}
		else
			m_Shader = Renderer::GetShader(Renderer::Shaders::Mesh_P_N_T);
	}
	void SpriteMeshes::RenderImGui()
	{
		Sprite::RenderImGui();
		ImGui::ColorEdit4("Mesh Color", &m_Color[0].r, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf);
	}
}