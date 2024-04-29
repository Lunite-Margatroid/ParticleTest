#pragma once
#include "Interface/ImGuiInterface.h"
namespace ptt
{
	class DemoScene
	{
	protected:

	public:
		DemoScene();
		virtual ~DemoScene();

		virtual bool ShouleClose();
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void RenderImGui();
	
	};

	typedef std::pair<std::function<DemoScene* ()>, std::string> SceneItem;


	class MenuScene :public DemoScene
	{
	private:
		std::vector<SceneItem> m_Menu;
		DemoScene* m_CurrentScene;
	public:
		MenuScene();
		~MenuScene();
		void RenderImGui();
		void Render();
		void Update(float deltaTime);

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
	};
}