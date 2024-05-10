#include "pch.h"
#include "SpriteTest.h"

namespace ptt
{
	SpriteTest::SpriteTest()
	{
		m_RootObj = std::make_unique<SceneObj>(nullptr, nullptr, "Root Obj");
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite(), "Quad Mesh");
		m_RootObj->PushChild(m_SelectedObj);
		m_Camera = std::make_unique<Camera3D>();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	SpriteTest::~SpriteTest()
	{
		glDisable(GL_BLEND);
	}
	void SpriteTest::DrawObjTree(const SceneObj& objNode)
	{
		static ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_None;
		flag = ImGuiTreeNodeFlags_None;
		flag |= ImGuiTreeNodeFlags_DefaultOpen;

		// 如果没有子节点 设置为叶子节点
		if (!objNode.HasChild())
		{
			flag |= ImGuiTreeNodeFlags_Leaf;
		}

		// 如果当前节点为选中节点 设置为选中状态
		if (m_SelectedObj == &objNode)
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (ImGui::TreeNodeEx(objNode.GetObjName().c_str(), flag))
		{
			if (ImGui::IsItemClicked())
			{// 点击当前节点 设置为选中节点
				m_SelectedObj = const_cast<SceneObj*>(&objNode);
			}
			if (objNode.HasChild())
				for (const SceneObj* obj : objNode.GetChildren())
				{
					DrawObjTree(*obj);
				}
			ImGui::TreePop();
		}
	}
	void SpriteTest::Render()
	{
		Renderer::SetCurrentCamera(m_Camera.get());
		m_RootObj->Render();
	}
	void SpriteTest::RenderImGui()
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera)
		{
			const glm::vec3& cameraPos = camera->GetPosition();
			const glm::vec3& cameraAhead = camera->GetAhead();
			ImGui::Text("CameraPos: %.2f  %.2f  %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
			ImGui::Text("CameraAhead: %.2f  %.2f  %.2f", cameraAhead.x, cameraAhead.y, cameraAhead.z);
		}
		ImGui::SeparatorText("Obj Tree");
		DrawObjTree(*m_RootObj);
		m_SelectedObj->RenderImGui();
	}
	void SpriteTest::Update(float deltaTime)
	{
		m_Camera->Update(deltaTime);
		m_RootObj->Update(deltaTime);
	}
}