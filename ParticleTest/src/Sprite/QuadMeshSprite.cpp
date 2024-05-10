#include "pch.h"
#include "QuadMeshSprite.h"


namespace ptt
{
	void QuadMeshSprite::Init()
	{
		const float tt = 1000.0f;
		float vertice[] =
		{
			// x      z
			-tt, -tt,
			-tt, tt,
			tt, tt,
			tt, -tt
		};

		m_Buffer.Init(sizeof(vertice), vertice, GL_STATIC_DRAW);
		m_VAO.SetVB(m_Buffer.GetID());
		m_VAO.PushAttrib<float>(2);
		m_VAO.ApplyLayout();
		m_VAO.SetMetaType(GL_TRIANGLE_FAN);
	}
	QuadMeshSprite::QuadMeshSprite() :
		m_MeshColor(1.0f, 1.0f, 1.0f, 1.0f)
	{
		Init();
		
	}
	QuadMeshSprite::~QuadMeshSprite()
	{
		
	}
	void QuadMeshSprite::SetMeshColor(const glm::vec4& color)
	{
		m_MeshColor = color;
	}
	void QuadMeshSprite::Render(const glm::mat4& modelTrans)
	{
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::QuadMesh);
		ASSERT(shader != nullptr);
		Camera* camera = Renderer::GetCurrentCamera();
		ASSERT(camera != nullptr);
		static glm::mat4 mvpTrans(1.0f);
		mvpTrans = camera->GetProjectionTrans() * camera->GetViewTrans() * modelTrans;
		shader->Bind();
		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		shader->SetUniform4f("u_MeshColor", m_MeshColor.r, m_MeshColor.g, m_MeshColor.b, m_MeshColor.a);

		m_VAO.DrawArray(4, 0);
	}
	void QuadMeshSprite::RenderImGui()
	{
		ImGui::SeparatorText("Quad Mesh Color");
		ImGui::ColorEdit4("Mesh Color", &m_MeshColor.r);
	}
}