#pragma once
#include "demoscene/DemoScene.h"

namespace ptt
{
	class ImGuiWindows
	{
	protected:
		std::string m_keyString;
		bool m_Open;
	public:
		ImGuiWindows(const std::string& keyString);
		virtual ~ImGuiWindows();

		virtual void ShowWindow() = 0;
		virtual void Update(float deltaTime);

		bool IsOpen()const;
		void CloseWindow();
		void OpenWindow();
		const std::string& GetWindowString() const;
		operator bool();
		bool* GetBoolPtr();
	};
}