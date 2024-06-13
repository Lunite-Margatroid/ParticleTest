#include "pch.h"
#include "ImGuiDialogModal.h"

namespace ptt
{
	ImGuiDialogModal::ImGuiDialogModal(const std::string& key)
		:ImGuiDialog(key)
	{
	}
	bool ImGuiDialogModal::WindowBegin()
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = g.CurrentWindow;

		if (!ImGui::IsPopupOpen(m_ImGui_ID, ImGuiPopupFlags_None))
		{
			g.NextWindowData.ClearFlags(); // We behave like Begin() and need to consume those values
			return false;
		}

		if ((g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasPos) == 0)
		{
			const ImGuiViewport* viewport = window->WasActive ? window->Viewport : ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
		}
		ImGuiWindowFlags flags = 0;
		flags |= ImGuiWindowFlags_Popup | ImGuiWindowFlags_Modal | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking \
			| ImGuiWindowFlags_AlwaysAutoResize;
		bool is_open = ImGui::Begin(m_keyString.c_str(), &m_Open, flags);

		if (!is_open || !m_Open) // NB: is_open can be 'false' when the popup is completely clipped (e.g. zero size display)
		{
			ImGui::EndPopup();
			if (is_open)
				ImGui::ClosePopupToLevel(g.BeginPopupStack.Size, true);
			return false;
		}

		return is_open;
	}
}