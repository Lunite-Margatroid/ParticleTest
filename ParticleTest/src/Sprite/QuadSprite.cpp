#include "pch.h"
#include "QuadSprite.h"

namespace ptt
{
	void QuadSprite::Init()
	{
		m_vao = Renderer::GetVertexArray(Renderer::VertexArrays::Quad_V_N_T);

		//m_Textures.push_back(Texture(Renderer::LoadTexture("./res/img/marisa.jpg")));
		Renderer::LoadTexture("./res/img/marisa.jpg");
	}
	//void QuadSprite::TextureSelector()
	//{
	//	int count = 1;
	//	const std::unordered_map<std::string, LM::Texture*>& textureMap = Renderer::GetTextureMap();
	//	for (int i =0;i < m_Textures.size();i++)
	//	{// 对于每一个 m_Texture 都有一个combo
	//		ImGui::BeginChild(Renderer::GetTextureComboName(count).c_str(), 
	//			ImVec2(0.0f, 0.0f),
	//			ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY);
	//		if (ImGui::BeginCombo(Renderer::GetTextureComboName(count).c_str(), m_Textures[i].m_Texture->GetTextureName().c_str()))
	//		{
	//			int n = Renderer::GetTextureCount();
	//			for (const auto& pTex: textureMap) // 遍历renderer所有纹理
	//			{
	//				bool isSelected = (pTex.second == m_Textures[i].m_Texture);// 与当前纹理是同一个 isSelected = true
	//				if (ImGui::Selectable(pTex.first.c_str(), isSelected))
	//				{
	//					m_Textures[i].m_Texture = pTex.second;
	//				}
	//				if (isSelected)
	//					ImGui::SetItemDefaultFocus();
	//			}
	//			ImGui::EndCombo();
	//		}
	//		ImGui::DragFloat2("offset", &m_Textures[i].offsetx, 0.01f, 0.0f, 1.0f,
	//			"%.3f",
	//			ImGuiSliderFlags_AlwaysClamp);
	//		ImGui::DragFloat2("scale", &m_Textures[i].scalex, 0.05f, 0.05f, 10.0f,
	//			"%.3f",
	//			ImGuiSliderFlags_AlwaysClamp);
	//		ImGui::EndChild();
	//		count++;
	//	}
	//	
	//}
	QuadSprite::QuadSprite(bool init)
	{
		if (init)
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
		shader->Bind();
		SetUniformMaterial(shader);

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

		m_vao->DrawArray();
	}
	void QuadSprite::RenderImGui()
	{
		Sprite::RenderImGui();
		ImGui::ColorEdit4("Mesh Color", &m_Color[0].r, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf);
		//TextureSelector();
		MaterialEditor();
	}
}