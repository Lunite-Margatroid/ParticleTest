#include "pch.h"
#include "AddObjectDialog.h"

namespace ptt
{
	void AddObjectDialog::Init()
	{
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::None);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Quad);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Cube);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Sphere);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Skybox);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Custom);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Firework);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::Hanabi);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::QuadMesh);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::DirectionalLight);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::PointLight);
		m_SpriteTypes.push_back(DemoSceneModel::SpriteType::SpotLight);

		m_NameMap[DemoSceneModel::SpriteType::None]				= std::string("None");
		m_NameMap[DemoSceneModel::SpriteType::Quad]				= std::string("Quad");
		m_NameMap[DemoSceneModel::SpriteType::Cube]				= std::string("Cube");
		m_NameMap[DemoSceneModel::SpriteType::Sphere]			= std::string("Sphere");
		m_NameMap[DemoSceneModel::SpriteType::Skybox]			= std::string("Skybox");
		m_NameMap[DemoSceneModel::SpriteType::Custom]			= std::string("Customed");
		m_NameMap[DemoSceneModel::SpriteType::Firework]			= std::string("Firework");
		m_NameMap[DemoSceneModel::SpriteType::Hanabi]			= std::string("Hanabi");
		m_NameMap[DemoSceneModel::SpriteType::QuadMesh]			= std::string("Quad Mesh");
		m_NameMap[DemoSceneModel::SpriteType::DirectionalLight] = std::string("Directional Light");
		m_NameMap[DemoSceneModel::SpriteType::PointLight]		= std::string("Point Light");
		m_NameMap[DemoSceneModel::SpriteType::SpotLight]		= std::string("Spot Light");

		memset(m_InputText, 0, 128);

		m_SelectedSprite = DemoSceneModel::SpriteType::Quad;

		m_IsAnimatable = false;
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
			ImGui::Checkbox("Animatable", &m_IsAnimatable);
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
					m_Scene->AddSceneObject(m_SelectedSprite, std::string(m_InputText), m_IsAnimatable);
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