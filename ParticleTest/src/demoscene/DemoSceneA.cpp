#include "pch.h"
#include "DemoSceneA.h"
#include "Application.h"

namespace ptt
{
	void DemoSceneA::Init()
	{
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite(), "Quad Mesh");
		m_RootObj->PushChild(m_SelectedObj);

		m_SelectedObj = new SceneObj(nullptr, new Hanabi(300), "Hanabi");
		m_RootObj->PushChild(m_SelectedObj);

		m_SelectedObj->SetPosition(glm::vec3(0.0f, 50.0f, -50.0f));

		m_SelectedObj = new SceneObj(nullptr,
			new QuadSprite(),
			"Quad");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetPosition(glm::vec3(2.0f, 2.0f, 2.0f));

		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "Cube1");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetPosition(glm::vec3(-4.0f, 4.0f, 4.0f));
		m_SelectedObj->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "Cube2");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetPosition(glm::vec3(-4.0f, 4.0f, 4.0f));

		m_SelectedObj = new SceneObj(nullptr, new CubeSprite(), "Cube3");
		m_RootObj->PushChild(m_SelectedObj);
		m_SelectedObj->SetPosition(glm::vec3(-4.0f, 4.0f, 4.0f));
		m_SelectedObj->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

	}
	DemoSceneA::DemoSceneA(bool init)
	{
		m_RootObj = std::make_unique<SceneObj>(nullptr, nullptr, "Root Obj");
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_SelectedObj = m_RootObj.get();
		m_MainCamera = dynamic_cast<CameraObj*>(new PerspectiveCamera(m_RootObj.get(), nullptr, "Perspective Camera"));
		CameraObj* orthoCamera = dynamic_cast<CameraObj*>(new OrthoCamera(m_RootObj.get(), nullptr, "Ortho Camera"));
		Renderer::SetCurrentCamera(m_MainCamera);
		if (init)
			Init();
	}

	DemoSceneA::DemoSceneA()
	{
		m_RootObj = std::make_unique<SceneObj>(nullptr, nullptr, "Root Obj");
		m_SelectedObj = m_RootObj.get();
		m_MainCamera = dynamic_cast<CameraObj*>(new PerspectiveCamera(m_RootObj.get(), nullptr, "Perspective Camera"));
		CameraObj* orthoCamera = dynamic_cast<CameraObj*>(new OrthoCamera(m_RootObj.get(), nullptr, "Ortho Camera"));
		Renderer::SetCurrentCamera(m_MainCamera);
		Init();
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	DemoSceneA::~DemoSceneA()
	{
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
	}
	void DemoSceneA::Render()
	{
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		// 渲染不透明物体
		glEnable(GL_STENCIL_TEST);
		glStencilMask(0x01);
		glStencilFunc(GL_ALWAYS, 0x01, 0x01);
		glStencilOp(GL_KEEP, GL_KEEP,GL_REPLACE);
		m_RootObj->Render();
		// 渲染天空盒
		glStencilFunc(GL_EQUAL, 0x00, 0x01);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glDepthMask(0x00);
		Renderer::RendererSkybox();
		// 渲染透明物体
		glStencilFunc(GL_ALWAYS, 0x00, 0x00);
		Renderer::RenderTransparencySprite();
	}
	void DemoSceneA::RenderImGui()
	{
		ImGui::Text("FPS: %.2f", Application::GetFPS());
		if (m_MainCamera)
		{
			const glm::vec3& cameraPos = m_MainCamera->GetPosition();
			const glm::vec3& cameraHead = m_MainCamera->GetHeadTo();
			ImGui::Text("CameraPos: %.2f  %.2f  %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
			ImGui::Text("CamearHeadTo: %.2f %.2f %.2f", cameraHead.x, cameraHead.y, cameraHead.z);
		}
		ImGui::SeparatorText("Obj Tree");
		DrawObjTree(*m_RootObj);
		m_SelectedObj->RenderImGui();
	}
	void DemoSceneA::Update(float deltaTime)
	{
		m_RootObj->Update(deltaTime);
	}

	void DemoSceneA::SetMainCamera(CameraObj* camera)
	{
		m_MainCamera = camera;
		Renderer::SetCurrentCamera(m_MainCamera);
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
				ImGuiIO& io = ImGui::GetIO(); (void)io;

				//双击将镜头对准目标
				if (io.MouseDoubleClicked[0])
				{
					if (CameraObj* camera = const_cast<CameraObj*>(Renderer::GetCurrentCamera()))
					{
						camera->HeadTo(glm::vec3(m_SelectedObj->GetModelTrans()[3]));
					}
				}
			}
			
			// 拖拽事件
			if (ImGui::BeginDragDropSource())
			{
				ImGui::Text(objNode.GetObjName().c_str());
				const SceneObj** SceneObj_ptr = const_cast<const SceneObj**>(new SceneObj*);
				*SceneObj_ptr = &objNode;
				ImGui::SetDragDropPayload("SceneObj_ptr", SceneObj_ptr, sizeof(void*));
				delete SceneObj_ptr;
				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (ImGuiPayload* data = const_cast<ImGuiPayload*>(ImGui::AcceptDragDropPayload("SceneObj_ptr")))
				{
					if (data->IsDelivery())
					{
						SceneObj* obj = *(SceneObj**)(data->Data);
						if (obj->GetParent())
						{
							const_cast<SceneObj&>(objNode).PushChild(obj);
						}
					}
				}
				ImGui::EndDragDropTarget();
			}

			if (objNode.HasChild())
				for (const SceneObj* obj : objNode.GetChildren())
				{
					DrawObjTree(*obj);
				}
			ImGui::TreePop();
		}
	}
	
}