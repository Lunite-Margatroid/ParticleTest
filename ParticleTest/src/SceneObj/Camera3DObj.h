#pragma once
#include "CameraObj.h"

namespace ptt
{
	class Camera3DObj : public CameraObj
	{
	protected:
		float m_ViewRangeScale;

		float m_SenRad;				// Sensitivity Of rotate
		float m_SenPos;				// Sensitivity Of Move
		float m_SenViewRange;		// Sensitivity of view range change

		float m_Near;
		float m_Far;


	public:
		Camera3DObj(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void Move(Direction dir, float len);
		void RotateYaw(float yaw);
		void RotateRoll(float roll);
		void RotatePitch(float pitch);
		void ViewRangeChange(float delta);

		void Update(float deltaTime) override;

		void SetNear(float near);
		void SetFar(float far);

		float GetNear() const;
		float GetFar() const;
	};
}