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
		m_ShaderName = LM::Shaders::QuadMesh;
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
		SelectShader();
		if(m_Shader == nullptr)
			return;

		Camera* camera = Renderer::GetCurrentCamera();

		if (camera == nullptr)
			return;
		static glm::mat4 mvpTrans(1.0f);
		mvpTrans = camera->GetProjectionTrans() * camera->GetViewTrans() * modelTrans;
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader->SetUniform4f("u_MeshColor", m_MeshColor.r, m_MeshColor.g, m_MeshColor.b, m_MeshColor.a);

		m_VAO.DrawArray(4, 0);
	}
	void QuadMeshSprite::RenderImGui()
	{
		Sprite::RenderImGui();
		ImGui::SeparatorText("Quad Mesh Color");
		ImGui::ColorEdit4("Mesh Color", &m_MeshColor.r);
	}
}