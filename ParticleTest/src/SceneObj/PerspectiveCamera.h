#pragma once
#include "Camera3DObj.h"

namespace ptt
{
	class PerspectiveCamera : public Camera3DObj
	{
	protected:
		float m_Width;
		float m_Height;

		float m_ViewRange;
		

		void UpdateProjectionTrans() override;
		void UpdateVPTrans() override;
	public:
		PerspectiveCamera(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void Update(float deltaTime) override;

		float GetWidth() const;
		float GetHeight() const;
		float GetViewRange()const;

		void SetWidth(float width);
		void SetHeight(float height);
		void SetViewRange(float rad);
	};
}