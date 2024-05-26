#include "pch.h"
#include "ImGuiWindows.h"

namespace ptt
{
	ImGuiWindows::ImGuiWindows(const std::string& keyString)
		:m_keyString(keyString), m_Open(true)
	{
	}
	ImGuiWindows::~ImGuiWindows()
	{
	}
	void ImGuiWindows::Update(float deltaTime)
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
	ImGuiWindows::operator bool()
	{
		return m_Open;
	}
	bool* ImGuiWindows::GetBoolPtr()
	{
		return &m_Open;
	}
}