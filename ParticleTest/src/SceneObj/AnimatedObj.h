#pragma once
#include "SceneObj.h"
#include "Animation/FrameNode.h"

namespace ptt
{
	class AnimatedObj : public SceneObj
	{
	protected:
		FrameNode m_FrameNode;
		bool m_bAnimated;

	public:
		AnimatedObj(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void Update(float deltaTime) override;
		void ReadAnimationScript(const std::string& path);
		void RenderImGui() override;
		void EnableAnimation(bool enableAnimation);
		bool IsAnimated() const;
	};
}