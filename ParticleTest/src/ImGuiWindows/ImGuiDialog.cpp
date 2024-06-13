#include "pch.h"
#include "ImGuiDialog.h"

namespace ptt
{
	ImGuiDialog::ImGuiDialog(const std::string& key)
		:ImGuiWindows(key)
	{
		
	}
	void ImGuiDialog::UpdateId()
	{
		ImGuiContext& g = *GImGui;
		m_ImGui_ID = g.CurrentWindow->GetID(m_keyString.c_str());
		m_Open = true;
	}
	void ImGuiDialog::Popup()
	{
		ImGui::OpenPopupEx(m_ImGui_ID);
	}
}