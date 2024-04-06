#pragma once

namespace ptt
{
	class Application
	{
	protected:
		void Init();


	public:
		Application();
		virtual ~Application();

		void Render();


	};
}