#include "pch.h"
#include "QuadSprite.h"

namespace ptt
{
	void QuadSprite::Init()
	{
		float vertice[]
		{
			// postion float 3		normal vec float3    texture coordiate float 2
			-1.0f, 0.0f, -1.0f,   0.0f, 1.0f,0.0f,		0.0f, 0.0f,
			1.0f, 0.0f, -1.0f,   0.0f, 1.0f,0.0f,		1.0f, 0.0f,
			1.0f, 0.0f, 1.0f,   0.0f, 1.0f,0.0f,		1.0f, 1.0f,
			-1.0f, 0.0f, 1.0f,   0.0f, 1.0f,0.0f,		0.0f, 1.0f,
		};
		ASSERT(sizeof(GLfloat) == sizeof(float));

		m_vbo.Init(sizeof(GLfloat) * 4 * 8, vertice, GL_STATIC_DRAW);

		m_vao.SetVB(m_vbo.GetID());
		m_vao.SetMetaType(GL_TRIANGLE_FAN);

		m_vao.PushAttrib<float>(3); // postion 3 float
		m_vao.PushAttrib<float>(3); // normal vec 3 float
		m_vao.PushAttrib<float>(2);	// texture coordiate float 2
		m_vao.ApplyLayout();

		//m_Textures.push_back(Renderer::LoadTexture("./res/img/Rumia.jpg"));
		m_Textures.push_back(0);
		Renderer::LoadTexture("./res/img/marisa.jpg");
	}
	void QuadSprite::TextureSelector()
	{
		int count = 1;
		for (unsigned int &tex : m_Textures)
		{// 对于每一个 m_Texture 都有一个combo

			if (ImGui::BeginCombo(Renderer::GetTextureComboName(count).c_str(), Renderer::GetTextureName(tex).c_str()))
			{
				int n = Renderer::GetTextureCount();
				for (int i = 0; i < n; i++) // 遍历renderer所有纹理
				{
					bool isSelected = (i == tex);// 与当前纹理是同一个 isSelected = true
					if (ImGui::Selectable(Renderer::GetTextureName(i).c_str(), isSelected))
					{
						tex = i;
					}
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			count++;
		}
		
	}
	QuadSprite::QuadSprite()
	{
		Init();
	}
	QuadSprite::~QuadSprite()
	{
	}
	void QuadSprite::Render(const glm::mat4& modelTrans)
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::Mesh_V_N_T);
		if (shader == nullptr)
			return;

		LM::Texture* tex = Renderer::GetTexture(m_Textures[0]);
		tex->Bind();
		shader->Bind();
		shader->SetUniformTexture("u_Tex", tex->GetIndex());

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

		m_vao.DrawArray(4);
	}
	void QuadSprite::RenderImGui()
	{
		ImGui::SeparatorText("Sprite Property");
		ImGui::ColorEdit4("Mesh Color", &m_Color[0].r, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf);
		TextureSelector();
	}
}