#pragma once
#include "ImGuiDialog.h"

namespace ptt
{
	class DialogManager
	{
	private:
		std::unordered_map<std::string, ImGuiDialog*> m_Dialogs;
	public:
		DialogManager();
		~DialogManager();

		template<typename T>
		void GenDialog(const std::string& name)
		{
			if (m_Dialogs.find(name) == m_Dialogs.end())
			{
				T* ptr = new T(name);
				ImGuiDialog* dialog = dynamic_cast<ImGuiDialog*>(ptr);
				if (dialog)
				{
					m_Dialogs[name] = dialog;
				}
				else
				{
					delete ptr;
					std::cout << "[ERROR] Wrong Type.\n";
				}
			}
			else
			{
				std::cout << "[ERROR] Same Dialog Title.\n";
			}
		}

		void Update();
		void Popup(const std::string& name);
		void ShowWindow(const std::string& name);
		ImGuiDialog* GetDialog(const std::string& name);
	};
}