#include "pch.h"
#include "Camera3DObj.h"

namespace ptt
{
	Camera3DObj::Camera3DObj(SceneObj* parent, Sprite* sprite, const std::string& objName) :
		CameraObj(parent, sprite, objName),
		m_ViewRangeScale(1.0f),
		m_SenPos(5.0f),
		m_SenRad(1.0f),
		m_SenViewRange(0.01f),
		m_Near(0.1f),
		m_Far(100.0f)
	{
	}
	void Camera3DObj::Move(Direction dir, float len)
	{
		switch (dir)
		{
		case Direction::front:
			m_Position += len * m_SenPos * m_Front;
			break;
		case Direction::back:
			m_Position -= len * m_SenPos * m_Front;
			break;
		case Direction::right:
			m_Position += len * m_SenPos * m_Right;
			break;
		case Direction::left:
			m_Position -= len * m_SenPos * m_Right;
			break;
		case Direction::up:
			m_Position.y += len * m_SenPos;
			break;
		case Direction::down:
			m_Position.y -= len * m_SenPos;
			break;
		default:break;
		};
	}
	void Camera3DObj::RotateYaw(float yaw)
	{
		m_Yaw += yaw * m_SenRad;
	}
	void Camera3DObj::RotateRoll(float roll)
	{
		m_Roll += roll * m_SenRad;
	}
	void Camera3DObj::RotatePitch(float pitch)
	{
		m_Pitch += pitch * m_SenRad;
		if (m_Pitch > 1.5f) m_Pitch = 1.5f;
		if (m_Pitch < -1.5f) m_Pitch = -1.5f;
	}
	void Camera3DObj::ViewRangeChange(float delta)
	{
		m_SenViewRange += delta * m_SenViewRange;
	}
	void Camera3DObj::Update(float deltaTime)
	{
		AnimatedObj::Update(deltaTime);
		UpdateDirectionVec();
		UpdateVPTrans();
	}
	void Camera3DObj::SetNear(float near)
	{
		m_Near = near;
	}
	void Camera3DObj::SetFar(float far)
	{
		m_Far = far;
	}
	float Camera3DObj::GetNear() const
	{
		return m_Near;
	}
	float Camera3DObj::GetFar() const
	{
		return m_Far;
	}
}