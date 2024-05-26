#include "pch.h"
#include "DemosceneLoader.h"

namespace ptt
{
	DemosceneLoader::DemosceneLoader(const std::string& keyStirng)
		:ImGuiWindows(keyStirng), m_Scene(nullptr)
	{
	}
	DemosceneLoader::~DemosceneLoader()
	{
		if (m_Scene)
			delete m_Scene;
	}
	void DemosceneLoader::SetScene(DemoScene* scene)
	{
		m_Scene = scene;
	}
	DemoScene* DemosceneLoader::GetScene()
	{
		return m_Scene;
	}
	void DemosceneLoader::ShowWindow()
	{
		//static char sceneTitle[128];
		ImGui::Begin(m_keyString.c_str(), &m_Open);
		for (auto& item : m_Menu)
		{
			if (ImGui::Button(item.second.c_str()))
			{
				if (m_Scene)
				{
					delete m_Scene;
					m_Scene = nullptr;
				}
				m_Scene = item.first();
				//strcpy(sceneTitle, item.second.c_str());
			}
		}
		ImGui::End();
	}
}