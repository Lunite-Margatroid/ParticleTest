#include "pch.h"
#include "ImGuiWindows.h"

namespace ptt
{
	ImGuiWindows::ImGuiWindows(const std::string& keyString)
		:m_keyString(keyString), m_Open(false)
	{
	}
	ImGuiWindows::~ImGuiWindows()
	{
	}
	bool ImGuiWindows::IsOpen() const
	{
		return m_Open;
	}
	void ImGuiWindows::CloseWindow()
	{
		m_Open = false;
	}
	void ImGuiWindows::OpenWindow()
	{
		m_Open = true;
	}
	const std::string& ImGuiWindows::GetWindowString() const
	{
		return m_keyString;
	}
}