#pragma once
#include "ImGuiDialog.h"

namespace ptt
{
	class ImGuiDialogModal : public ImGuiDialog
	{
	protected:

	public:
		ImGuiDialogModal(const std::string& key);
		~ImGuiDialogModal() = default;

		bool WindowBegin();
		void WindowEnd();
	};
}