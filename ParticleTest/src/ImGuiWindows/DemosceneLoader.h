#pragma once
#include "ImGuiWindows.h"


namespace ptt
{
	typedef std::pair<std::function<DemoScene* ()>, std::string> SceneItem;

	class DemosceneLoader : public ImGuiWindows
	{
	protected:
		std::vector<SceneItem> m_Menu;
		DemoScene* m_Scene;
	public:
		DemosceneLoader(const std::string& keyStirng);
		~DemosceneLoader();

		void SetScene(DemoScene* scene);
		DemoScene* GetScene();

		template<typename T>
		void RegistDemoScene(const std::string& title)
		{
			m_Menu.emplace_back(
				std::make_pair
				(
					[]()
					{
						return new T();
					}
					,
						title
						)
			);
		}

		virtual void ShowWindow() override;
	};
}