#include "pch.h"
#include "AddCameraDialog.h"

namespace ptt
{
	void AddCameraDialog::Init()
	{
		m_CameraTypes.push_back(CameraObj::CameraType::PerspectiveCamera3D);
		m_CameraTypes.push_back(CameraObj::CameraType::OrthographicCamera3D);

		m_NameMap[CameraObj::CameraType::PerspectiveCamera3D]	= std::string("Perspective Camera 3D");
		m_NameMap[CameraObj::CameraType::OrthographicCamera3D]	= std::string("Orthographic Camera 3D");

		m_Selected = CameraObj::CameraType::PerspectiveCamera3D;
		memset(m_InputText, 0, 128);
	}
	AddCameraDialog::AddCameraDialog(const std::string& dialogName)
		:ImGuiDialogModal(dialogName)
	{
		m_Scene = nullptr;
		Init();
	}
	void AddCameraDialog::ShowWindow()
	{
		if (WindowBegin())
		{
			ImGui::InputText("Camera Name", m_InputText, 128);
			if (ImGui::BeginCombo("Camera Type", m_NameMap[m_Selected].c_str()))
			{
				for (auto i : m_CameraTypes)
				{
					bool isSelected = m_Selected == i;
					if (ImGui::Selectable(m_NameMap[i].c_str(), &isSelected))
					{
						m_Selected = i;
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
					m_Scene->AddCamera(m_Selected, std::string(m_InputText));
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
	void AddCameraDialog::InitWindow(DemoSceneModel* scene)
	{
		m_Scene = scene;
	}
}