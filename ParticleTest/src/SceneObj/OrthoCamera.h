#pragma once
#include "Camera3DObj.h"

namespace ptt
{
	class OrthoCamera : public Camera3DObj
	{
	protected:
		float m_Left;
		float m_Right;
		float m_Top;
		float m_Bottom;

		virtual void UpdateProjectionTrans() override;
		virtual void UpdateVPTrans() override;
	public:
		OrthoCamera(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void Update(float deltaTime) override;

		void SetViewCube(float left, float right, float top, float bottom, float near, float far);
		void SetLeft(float left);
		void SetRight(float right);
		void SetTop(float top);
		void SetBottom(float bottom);

		float GetLeft() const;
		float GetRight() const;
		float GetTop() const;
		float GetBottom() const;
	};
}