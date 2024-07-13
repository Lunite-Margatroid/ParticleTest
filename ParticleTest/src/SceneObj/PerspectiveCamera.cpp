#include "pch.h"
#include "PerspectiveCamera.h"

namespace ptt
{
	void PerspectiveCamera::UpdateProjectionTrans()
	{
		m_ProjectionTrans = glm::perspective(m_ViewRange * m_ViewRangeScale, m_Width / m_Height, m_Near, m_Far);
	}
	void PerspectiveCamera::UpdateVPTrans()
	{
		UpdateViewTrans();
		UpdateProjectionTrans();
		m_VPTrans = m_ProjectionTrans * m_ViewTrans;
	}
	PerspectiveCamera::PerspectiveCamera(SceneObj* parent, Sprite* sprite, const std::string& objName)
		: 
		Camera3DObj(parent, sprite, objName),
		m_Width(16.f), m_Height(9.0f), m_ViewRange(PI / 4.f)
	{
	}
	void PerspectiveCamera::Update(float deltaTime)
	{
		AnimatedObj::Update(deltaTime);
		if (m_ParentObj)
			UpdateDirectionVec(glm::mat3(m_ParentObj->GetModelTrans()));
		else
			UpdateDirectionVec(glm::mat3(1.0f));
		UpdateVPTrans();
	}
	float PerspectiveCamera::GetWidth() const
	{
		return m_Width;
	}
	float PerspectiveCamera::GetHeight() const
	{
		return m_Height;
	}
	float PerspectiveCamera::GetViewRange() const
	{
		return m_ViewRange;
	}
	void PerspectiveCamera::SetWidth(float width)
	{
		m_Width = width;
	}
	void PerspectiveCamera::SetHeight(float height)
	{
		m_Height = height;
	}
	void PerspectiveCamera::SetViewRange(float rad)
	{
		m_ViewRange = rad;
	}
}