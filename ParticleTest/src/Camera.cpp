#include "pch.h"
#include "Camera.h"

namespace ptt
{
	Camera::Camera():m_ViewTrans(1.0f), m_ProjectionTrans(1.0f), m_Width(16.0f), m_Height(9.0f),m_Near(-1.0f),m_Far(1.f)
	{
	}
	Camera::~Camera()
	{
	}
	const glm::mat4& Camera::GetViewTrans() const
	{
		// TODO: insert return statement here
		return m_ViewTrans;
	}
	const glm::mat4& Camera::GetProjectionTrans() const
	{
		// TODO: insert return statement here
		return m_ProjectionTrans;
	}
	void Camera::SetNear(float near)
	{
		m_Near = near;
	}
	void Camera::SetFar(float far)
	{
		m_Far = far;
	}
	void Camera::SetWidth(float width)
	{
		m_Width = width;
	}
	void Camera::SetHeight(float height)
	{
		m_Height = height;
	}
}