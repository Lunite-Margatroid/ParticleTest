#include "pch.h"
#include "CameraObj.h"
#include "Application.h"
#include "demoscene/DemoSceneA.h"

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
		if (m_ParentObj)
			UpdateDirectionVec(glm::mat3(m_ParentObj->GetModelTrans()));
		else
			UpdateDirectionVec(glm::mat3(1.0f));
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
		glm::vec3 dir = target - glm::vec3(m_ModelTrans[3]);
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

	void CameraObj::RenderImGui()
	{
		AnimatedObj::RenderImGui();
		ImGui::Separator();
		if (ImGui::Button("SetMainCamera"))
		{
			DemoSceneA* scene = dynamic_cast<DemoSceneA*>(Application::GetCurrentScene());
			if (scene)
			{
				scene->SetMainCamera(this);
			}
		}
		
	}

	void CameraObj::UpdateDirectionVec(const glm::mat3& parentRotation)
	{
		m_HeadTo = glm::mat3(m_ModelTrans) * glm::vec3(0.0f, 0.0f, -1.0f);
		m_Right = parentRotation * glm::vec3(1.0f, 0.0f, 0.0f);
		m_Front = parentRotation * glm::vec3(0.0f, 0.0f, -1.0f);
		m_Up = parentRotation * glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat3 m = glm::mat3(glm::rotate(glm::mat4(1.0f), m_Yaw, m_Up));
		m_Front = m * m_Front;
		m_Right = m * m_Right;
	}
	void CameraObj::UpdateViewTrans()
	{
		glm::vec3 pos = glm::vec3(m_ModelTrans[3]);
		m_ViewTrans = glm::lookAt(pos, pos + m_HeadTo, m_Up);
	}
}