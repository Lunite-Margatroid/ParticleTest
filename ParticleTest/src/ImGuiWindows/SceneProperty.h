#pragma once
#include "ImGuiWindows.h"
#include "demoscene/DemoScene.h"


namespace ptt
{
	class SceneProperty : public ImGuiWindows
	{
	protected:
		DemoScene* m_Scene;
	public:
		SceneProperty(const std::string& keyString,DemoScene* scene);
		SceneProperty(const std::string& keyString);

		virtual void ShowWindow() override;

		void SetScene(DemoScene* scene);
		const DemoScene* GetScene() const;
	};
}