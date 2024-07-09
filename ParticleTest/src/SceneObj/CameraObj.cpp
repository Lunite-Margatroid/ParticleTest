#include "pch.h"
#include "CameraObj.h"

namespace ptt
{
	void CameraObj::UpdateVPTrans()
	{
		UpdateViewTrans();
		UpdateProjectionTrans();
		m_VPTrans = m_ProjectionTrans * m_ViewTrans;
	}
	CameraObj::CameraObj(SceneObj* parent, Sprite* sprite, const std::string& objName)
		:AnimatedObj(parent, sprite, objName), 
		m_ViewTrans(1.f), 
		m_ProjectionTrans(1.0f), 
		m_VPTrans(1.0f),
		m_HeadTo(0.0f, 0.0f, -1.0f),
		m_Right(1.0f, 0.0f, 0.0f),
		m_Front(0.0f, 0.0f, -1.0f)
	{
	}
	void CameraObj::Update(float deltaTime)
	{
		AnimatedObj::Update(deltaTime);
		UpdateDirectionVec();
		UpdateVPTrans();
	}
	const glm::mat4& CameraObj::GetViewTrans() const
	{
		return m_ViewTrans;
	}
	const glm::mat4& CameraObj::GetProjectionTrans() const
	{
		return m_ProjectionTrans;
	}
	const glm::mat4& CameraObj::GetVPTrans() const
	{
		return m_VPTrans;
	}

	const glm::vec3& CameraObj::GetHeadTo() const
	{
		// TODO: insert return statement here
		return m_HeadTo;
	}

	void CameraObj::HeadTo(const glm::vec3& target)
	{
		glm::vec3 dir = target - m_Position;
		float xz = sqrtf(dir.x * dir.x + dir.z * dir.z);
		if (xz > 0.0f)
		{
			m_Yaw = dir.x > 0 ? -acosf(-dir.z / xz) : acosf(-dir.z / xz);
		}

		float xyz = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		if (xyz > 0.0f)
		{
			m_Pitch = acos(xz / xyz);
			m_Pitch = dir.y > 0 ? m_Pitch : -m_Pitch;
			m_Pitch = m_Pitch < 1.5f ? m_Pitch : 1.5f;
			m_Pitch = m_Pitch > -1.5f ? m_Pitch : -1.5f;
		}
	}

	void CameraObj::UpdateDirectionVec()
	{
		m_Right.x = cosf(m_Yaw);
		m_Right.y = 0.f;
		m_Right.z = -sinf(m_Yaw);

		m_Front.x = m_Right.z;
		m_Front.y = 0.0f;
		m_Front.z = -m_Right.x;

		glm::mat4 rotationMat(1.f);
		QuaternionRotate(rotationMat, m_Qua);
		m_HeadTo = rotationMat * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	}
	void CameraObj::UpdateViewTrans()
	{
		m_ViewTrans = glm::lookAt(m_Position, m_Position + m_HeadTo, glm::vec3(0.0f, 1.0f, 0.f));
	}
}