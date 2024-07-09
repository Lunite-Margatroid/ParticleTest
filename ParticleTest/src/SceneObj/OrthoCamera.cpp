#include "pch.h"
#include "OrthoCamera.h"

namespace ptt
{
	void OrthoCamera::UpdateProjectionTrans()
	{
		m_ProjectionTrans = glm::ortho(m_Left * m_ViewRangeScale, m_Right * m_ViewRangeScale, 
			m_Bottom * m_ViewRangeScale, m_Top * m_ViewRangeScale, m_Near, m_Far);
	}
	void OrthoCamera::UpdateVPTrans()
	{
		UpdateViewTrans();
		UpdateProjectionTrans();
		m_VPTrans = m_ProjectionTrans * m_ViewTrans;
	}
	OrthoCamera::OrthoCamera(SceneObj* parent, Sprite* sprite, const std::string& objName)
		:Camera3DObj(parent, sprite, objName),
		m_Left(-8.f),
		m_Right(8.f),
		m_Top(4.5f),
		m_Bottom(-4.5f)
	{
	}
	void OrthoCamera::Update(float deltaTime)
	{
		AnimatedObj::Update(deltaTime);
		UpdateDirectionVec();
		UpdateVPTrans();
	}
	void OrthoCamera::SetViewCube(float left, float right, float top, float bottom, float near, float far)
	{
		m_Left = left;
		m_Right = right;
		m_Top = top;
		m_Bottom = bottom;
		m_Near = near;
		m_Far = far;
	}
	void OrthoCamera::SetLeft(float left)
	{
		m_Left = left;
	}
	void OrthoCamera::SetRight(float right)
	{
		m_Right = right;
	}
	void OrthoCamera::SetTop(float top)
	{
		m_Top = top;
	}
	void OrthoCamera::SetBottom(float bottom)
	{
		m_Bottom = bottom;
	}
	float OrthoCamera::GetLeft() const
	{
		return m_Left;
	}
	float OrthoCamera::GetRight() const
	{
		return m_Right;
	}
	float OrthoCamera::GetTop() const
	{
		return m_Top;
	}
	float OrthoCamera::GetBottom() const
	{
		return m_Bottom;
	}
}