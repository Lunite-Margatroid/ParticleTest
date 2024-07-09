#pragma once
#include "ImGuiWindows.h"
#include "demoscene/DemoScene.h"
#include "glObj/FrameBufferMS.h"
#include "Renderer/Renderer.h"
#include "SceneObj/Camera3DObj.h"

namespace ptt
{
	class SceneWindow : public ImGuiWindows
	{
	protected:
		DemoScene* m_Scene;

		int m_SceneWidth;
		int m_SceneHeight;

		LM::FrameBuffer m_Framebuffer;
		LM::FrameBufferMS m_FramebufferMS;
		LM::FrameBuffer* m_Current;

		float m_DeltaTime;
	public:
		SceneWindow(const std::string& keyString, int width, int height);
		SceneWindow(const std::string& keyString);
		void Init(int width, int height);
		void SetScene(DemoScene* scene);
		const DemoScene* GetScene() const;

		void SetMultisample(bool multisample);
		bool IsMultisample() const;
		virtual void ShowWindow() override;
		virtual void Update(float deltaTime) override;

		LM::FrameBuffer* GetFrameBuffer();
		LM::FrameBufferMS* GetFrameBufferMS();

	};
}