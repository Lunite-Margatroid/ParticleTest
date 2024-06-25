#include "pch.h"
#include "TestCube.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	void TestCube::Init()
	{
		float vertices[]
		{
			-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 
			1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
			1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f
		};
		unsigned int indices[]
		{
			0, 1, 2, 3, 4, 5, 6, 7, 0xffffffff, 
			2, 4, 0, 6, 1, 7, 3, 5
		};

		m_ShaderName = LM::Shaders::Mesh_P_N_T;
		m_VBO.Init(sizeof(vertices), vertices, GL_STATIC_DRAW);
		m_EBO.Init(17, indices, GL_STATIC_DRAW);
		m_VAO.SetMetaType(GL_TRIANGLE_STRIP);
		m_VAO.SetCount(17);
		m_VAO.SetEB(m_EBO.GetID());
		m_VAO.SetVB(m_VBO.GetID());
		m_VAO.PushAttrib<float>(3);
		m_VAO.PushAttrib<float>(3);
		m_VAO.PushAttrib<float>(2);
		m_VAO.ApplyLayout();
	}
	TestCube::TestCube()
	{
		Init();
	}
	TestCube::TestCube(bool init)
	{
		if (init)
			Init();
	}
	void TestCube::Render(const glm::mat4& modelTrans)
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;
		SelectShader();
		if (m_Shader == nullptr)
			return;
		
		m_Shader->Bind();
		SetUniformMaterial(m_Shader);

		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		mvpTrans = camera->GetProjectionTrans() * camera->GetViewTrans() * modelTrans;
		m_Shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader->SetUniform4f("u_Color", &m_Color[0].r);

		glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
		glPrimitiveRestartIndex(0xffffffff);
		m_VAO.DrawElement();
		glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
	}
	void TestCube::RenderImGui()
	{
		Sprite::RenderImGui();
		ImGui::ColorEdit4("Mesh Color", &m_Color[0].r, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf);
		MaterialEditor();
	}
}