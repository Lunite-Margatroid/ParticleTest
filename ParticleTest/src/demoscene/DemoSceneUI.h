#pragma once
#include "LightedDemoScene.h"

namespace ptt
{
	class DemoSceneUI : public LightedDemoScene
	{
	protected:
		LM::VertexBuffer m_uiBuffer;
		LM::VertexArray m_uiVertexArray;
		LM::ElementBuffer m_uiEleBuffer;


		virtual void Init();
		virtual void InitUI();
	public:
		DemoSceneUI();
		DemoSceneUI(bool init);
		virtual ~DemoSceneUI();
		virtual void RenderUI();
		void Render() override;
	};
}