#include "pch.h"
#include "DemoSceneA.h"

namespace ptt
{
	void DemoSceneA::Init()
	{
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite(), "Quad Mesh");
		m_RootObj->PushChild(m_SelectedObj);

		m_SelectedObj = new SceneObj(nullptr, new Hanabi(300), "Hanabi");
		m_RootObj->PushChild(m_SelectedObj);

		m_SelectedObj->SetPosition(glm::vec3(0.0f, 50.0f, -50.0f));

		m_Camera = Renderer::GetCamera(Renderer::Cameras::Camera3D_Alpha);
		Renderer::SetCurrentCamera(m_Camera);

		Camera3D* camera = dynamic_cast<Camera3D*>(m_Camera);
		camera->SetPos(glm::vec3(0.0f, 1.f, 0.0f));
		camera->SetEulerAngle(PI / 4, 0.0f, 0.0f);
	}
	DemoSceneA::DemoSceneA(bool init)
	{
		m_RootObj = std::make_unique<SceneObj>(nullptr, nullptr, "Root Obj");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (init)
			Init();
	}
	DemoSceneA::~DemoSceneA()
	{
		glDisable(GL_BLEND);
	}
	void DemoSceneA::Render()
	{
		m_RootObj->Render();
	}
	void DemoSceneA::RenderImGui()
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(m_Camera);
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
	void DemoSceneA::Update(float deltaTime)
	{
		m_Camera->Update(deltaTime);
		m_RootObj->Update(deltaTime);
	}

	void DemoSceneA::DrawObjTree(const SceneObj& objNode)
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
	DemoSceneA::DemoSceneA()
	{
		m_RootObj = std::make_unique<SceneObj>(nullptr, nullptr, "Root Obj");
		Init();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}