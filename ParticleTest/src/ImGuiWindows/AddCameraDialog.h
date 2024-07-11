#pragma once
#include "ImGuiDialogModal.h"
#include "demoscene/DemoSceneModel.h"
namespace ptt
{
	class AddCameraDialog : public ImGuiDialogModal
	{
	private:
		DemoSceneModel* m_Scene;
		std::vector<CameraObj::CameraType> m_CameraTypes;
		std::map<CameraObj::CameraType, std::string> m_NameMap;
		CameraObj::CameraType m_Selected;
		char m_InputText[128];

		void Init();
	public:
		AddCameraDialog(const std::string& dialogName);

		void ShowWindow() override;
		void InitWindow(DemoSceneModel* scene);


		

	};
}