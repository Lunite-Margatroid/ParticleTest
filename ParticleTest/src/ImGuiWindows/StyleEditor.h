#pragma once
#include "ImGuiWindows.h"

namespace ptt
{
	class StyleEditor : public ImGuiWindows
	{
	public:
		StyleEditor(const std::string& keyString);
		~StyleEditor();

		virtual void ShowWindow() override;
	};
}