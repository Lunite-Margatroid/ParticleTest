#pragma once
#include "ImGuiWindows.h"

namespace ptt
{
	class ImGuiDialog : public ImGuiWindows
	{
	protected:
		ImGuiID m_ImGui_ID;
	public:
		ImGuiDialog(const std::string& key);
		~ImGuiDialog() = default;
		void UpdateId();
		void Popup();

	};
}