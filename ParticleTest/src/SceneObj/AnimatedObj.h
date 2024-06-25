#pragma once
#include "SceneObj.h"
#include "Animation/FrameNode.h"

namespace ptt
{
	class AnimatedObj : public SceneObj
	{
	protected:
		FrameNode m_FrameNode;

	public:
		AnimatedObj(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void Update(float deltaTime) override;
		void ReadAnimationScript(const std::string& path);
		void RenderImGui() override;
	};
}