#pragma once
#include "Interface/ImGuiInterface.h"
#include "glObj/FrameBuffer.h"
#include "Camera3D.h"

namespace ptt
{
	class DemoScene
	{
	protected:

	public:
		DemoScene();
		virtual ~DemoScene();

		virtual bool ShouleClose();
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void RenderImGui();
	
	};
}
