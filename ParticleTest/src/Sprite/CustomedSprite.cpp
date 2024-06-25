#include "pch.h"
#include "CustomedSprite.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	void CustomedSprite::Init()
	{
		m_Mode = GL_POINTS;

		m_ShaderName = LM::Shaders::CustomedSprite_P_C;
		SelectShader();

		m_VertexArray.SetVB(m_VertexBuffer.GetID());
		m_VertexArray.PushAttrib<float>(3);
		m_VertexArray.PushAttrib<float>(4);
		m_VertexArray.ApplyLayout();

		m_VertexSize = 3.0f;
		m_SelectedVertex = -1;

		m_DrawModes[0] = GL_POINTS;
		m_DrawModes[1] = GL_LINES;
		m_DrawModes[2] = GL_LINE_LOOP;
		m_DrawModes[3] = GL_LINE_STRIP;
		m_DrawModes[4] = GL_TRIANGLES;
		m_DrawModes[5] = GL_TRIANGLE_STRIP;
		m_DrawModes[6] = GL_TRIANGLE_FAN;

		m_NameMap[GL_POINTS] = std::string("points");
		m_NameMap[GL_LINES] = std::string("lines");
		m_NameMap[GL_LINE_LOOP] = std::string("line loop");
		m_NameMap[GL_LINE_STRIP] = std::string("line strip");
		m_NameMap[GL_TRIANGLES] = std::string("triangles");
		m_NameMap[GL_TRIANGLE_STRIP] = std::string("triangle strip");
		m_NameMap[GL_TRIANGLE_FAN] = std::string("triangle fan");

	}
	CustomedSprite::CustomedSprite()
		:m_VertexBuffer(1024, GL_DYNAMIC_DRAW)
	{
		Init();
	}
	void CustomedSprite::UpdateVertexBuffer()
	{
		m_VertexBuffer.Clear();
		m_VertexBuffer.PushBack((void*)&m_Vertices[0], sizeof(Vertex) * m_Vertices.size());
	}
	void CustomedSprite::Render(const glm::mat4& modelTrans)
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;

		SelectShader();

		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		glm::mat4& mvTrans = Renderer::GetMVPTrans();
		mvTrans = camera->GetViewTrans() * modelTrans;
		mvpTrans = camera->GetProjectionTrans() * mvTrans;

		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader->SetUniform1f("u_Far", camera->GetFar());
		m_Shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));
		m_Shader->SetUniform1f("u_VertexSize", m_VertexSize);
		m_Shader->SetUniform1i("u_DrawMode", m_Mode);

		m_VertexArray.SetCount(m_Vertices.size());
		m_VertexArray.SetMetaType(m_Mode);
		m_VertexArray.DrawArray();
	}
	void CustomedSprite::RenderImGui()
	{
		Sprite::RenderImGui();

		ImGui::SliderFloat("Veretx Size", &m_VertexSize, 1.0f, 50.0f);
		char strVerticeAttrib[64];
		ImGui::Text("Vertex List");

		ImGui::BeginChild("Vertex List Child", ImVec2(0, 0), 
			ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_FrameStyle);
		//ImGui::BeginListBox("##Vertex List");
		for (int i = 0; i < m_Vertices.size(); i++)
		{
			unsigned char color[4];
			color[0] = (unsigned char)(m_Vertices[i].r * 255);
			color[1] = (unsigned char)(m_Vertices[i].g * 255);
			color[2] = (unsigned char)(m_Vertices[i].b * 255);
			color[3] = (unsigned char)(m_Vertices[i].a * 255);
			sprintf(strVerticeAttrib, "   x: %+3.2f y:%+3.2f z:%+3.2f", m_Vertices[i].x, m_Vertices[i].y, m_Vertices[i].z);
			bool isSelected = i == m_SelectedVertex;
			if (ImGui::Selectable(strVerticeAttrib, &isSelected))
			{
				m_SelectedVertex = i;
			}
			ImVec2 itemPos = ImGui::GetItemRectMin();
			ImVec2 itemSize = ImGui::GetItemRectSize();

			ImGui::GetWindowDrawList()->AddRectFilled
			(ImVec2(itemPos.x + 1, itemPos.y + 1), ImVec2(itemPos.x + itemSize.y - 2, itemPos.y + itemSize.y - 2), *(unsigned int*)color);
		}
		//ImGui::EndListBox(); // ##Vertex List
		ImGui::EndChild();	// Vertex List Child

		if(ImGui::BeginCombo("Draw Mode", m_NameMap[m_Mode].c_str()))
		{
			for (int i = 0; i < 7; i++)
			{
				bool isSelected = m_DrawModes[i] == m_Mode;
				if (ImGui::Selectable(m_NameMap[m_DrawModes[i]].c_str(), &isSelected))
				{
					m_Mode = m_DrawModes[i];
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Add"))
		{
			m_SelectedVertex = m_Vertices.size();
			m_Vertices.emplace_back(Vertex());
		}

		ImGui::SameLine();
		if (m_SelectedVertex >= 0)
		{
			if (ImGui::Button("Erase"))
			{
				auto iter = m_Vertices.begin();
				while (m_SelectedVertex-- > 0) iter++;
				m_Vertices.erase(iter);
			}
		}
		if (m_SelectedVertex >= 0)
		{
			ImGui::DragFloat3("Vertex Position", &m_Vertices[m_SelectedVertex].x, 0.01f, -10.0f, 10.0f);
			// ImGui::SliderFloat3("Position", &m_Vertices[m_SelectedVertex].x, -10.0f, 10.0f);
			ImGui::ColorEdit4("Vertex Color", &m_Vertices[m_SelectedVertex].r);
		}
		
	}
	void CustomedSprite::Update(float deltaTime)
	{
		UpdateVertexBuffer();
	}
	void CustomedSprite::AddVertex(Vertex vert)
	{
		m_Vertices.push_back(vert);
	}
}