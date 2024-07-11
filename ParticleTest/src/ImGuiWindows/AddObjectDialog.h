#pragma once
#include "ImGuiDialogModal.h"
#include "demoscene/DemoSceneModel.h"
namespace ptt
{
	class AddObjectDialog : public ImGuiDialogModal
	{
	protected:
		DemoSceneModel* m_Scene;
		std::vector<DemoSceneModel::SpriteType> m_SpriteTypes;
		std::map<DemoSceneModel::SpriteType, std::string> m_NameMap;
		DemoSceneModel::SpriteType m_SelectedSprite;
		char m_InputText[128];
		bool m_IsAnimatable;
		void Init();
	public:
		AddObjectDialog(const std::string& dialogName);

		void ShowWindow() override;
		void InitWindow(DemoSceneModel* scene);
	
	};
}