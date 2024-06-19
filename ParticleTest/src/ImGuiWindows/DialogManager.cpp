#include "pch.h"
#include "DialogManager.h"

namespace ptt
{
	DialogManager::DialogManager()
	{
	}
	DialogManager::~DialogManager()
	{
		for (auto& dialog : m_Dialogs)
		{
			delete dialog.second;
		}
	}
	void DialogManager::Update()
	{
		for (auto& dialog : m_Dialogs)
		{
			dialog.second->UpdateId();
		}
	}
	void DialogManager::Popup(const std::string& name)
	{
		if (m_Dialogs.find(name) != m_Dialogs.end())
		{
			m_Dialogs[name]->Popup();
		}
	}
	void DialogManager::ShowWindow(const std::string& name)
	{
		if (m_Dialogs.find(name) != m_Dialogs.end())
		{
			m_Dialogs[name]->ShowWindow();
		}
	}
	ImGuiDialog* DialogManager::GetDialog(const std::string& name)
	{
		if(m_Dialogs.find(name) != m_Dialogs.end())
			return m_Dialogs[name];
		return nullptr;
	}
}