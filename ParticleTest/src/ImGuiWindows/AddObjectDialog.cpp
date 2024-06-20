#include "pch.h"
#include "AddObjectDialog.h"

namespace ptt
{
	void AddObjectDialog::Init()
	{
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Quad);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Cube);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Sphere);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Skybox);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Custom);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Firework);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Hanabi);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::QuadMesh);

		m_NameMap[DemoSceneModel::SpriteType::Quad]		= std::string("Quad");
		m_NameMap[DemoSceneModel::SpriteType::Cube]		= std::string("Cube");
		m_NameMap[DemoSceneModel::SpriteType::Sphere]	= std::string("Sphere");
		m_NameMap[DemoSceneModel::SpriteType::Skybox]	= std::string("Skybox");
		m_NameMap[DemoSceneModel::SpriteType::Custom]	= std::string("Customed");
		m_NameMap[DemoSceneModel::SpriteType::Firework]	= std::string("Firework");
		m_NameMap[DemoSceneModel::SpriteType::Hanabi]	= std::string("Hanabi");
		m_NameMap[DemoSceneModel::SpriteType::QuadMesh]	= std::string("Quad Mesh");

		memset(m_InputText, 0, 128);

		m_SelectedSprite = DemoSceneModel::SpriteType::Quad;
	}
	AddObjectDialog::AddObjectDialog(const std::string& dialogName)
		:ImGuiDialogModal(dialogName)
	{
		m_Scene = nullptr;
		Init();
	}
	void AddObjectDialog::ShowWindow()
	{
		if (WindowBegin())
		{
			ImGui::InputText("Object Name", m_InputText, 128);
			if (ImGui::BeginCombo("Object Type", m_NameMap[m_SelectedSprite].c_str()))
			{
				for (auto i : m_SpriteTypes)
				{
					bool isSelected = m_SelectedSprite == i;
					if (ImGui::Selectable(m_NameMap[i].c_str(), &isSelected))
					{
						m_SelectedSprite = i;
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("OK"))
			{
				if (m_Scene)
				{
					m_Scene->AddSceneObject(m_SelectedSprite, std::string(m_InputText));
				}
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			WindowEnd();
		}
	}
	void AddObjectDialog::InitWindow(DemoSceneModel* scene)
	{
		m_Scene = scene;
	}
}