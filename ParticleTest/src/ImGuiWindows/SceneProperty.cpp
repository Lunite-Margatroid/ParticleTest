#include "pch.h"
#include "SceneProperty.h"

namespace ptt
{
	SceneProperty::SceneProperty(const std::string& keyString, DemoScene* scene)
		:ImGuiWindows(keyString), m_Scene(scene)
	{
	}
	SceneProperty::SceneProperty(const std::string& keyString)
		:ImGuiWindows(keyString),m_Scene(nullptr)
	{
	}
	void SceneProperty::ShowWindow()
	{
		ImGui::Begin(m_keyString.c_str(), &m_Open);
		if(m_Scene)
			m_Scene->RenderImGui();
		ImGui::End();
	}
	void SceneProperty::SetScene(DemoScene* scene)
	{
		m_Scene = scene;
	}
	const DemoScene* SceneProperty::GetScene() const
	{
		return m_Scene;
	}
}