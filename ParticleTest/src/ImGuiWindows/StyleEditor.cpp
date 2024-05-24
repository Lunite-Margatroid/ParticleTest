#include "pch.h"
#include "StyleEditor.h"

namespace ptt
{
	StyleEditor::StyleEditor(const std::string& keyString)
		:ImGuiWindows(keyString)
	{

	}
	StyleEditor::~StyleEditor()
	{
	}
	void StyleEditor::ShowWindow()
	{
		ImGui::Begin(m_keyString.c_str(), &m_Open);
		ImGui::ShowStyleEditor();
		ImGui::End();
	}
}