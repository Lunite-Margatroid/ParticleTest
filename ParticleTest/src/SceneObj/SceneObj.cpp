#include "pch.h"
#include "SceneObj.h"

namespace ptt
{
	void SceneObj::Clear()
	{
		for (auto child : m_ChildObj)
		{
			delete child;
		}
	}
	void SceneObj::UpdateQuaternion()
	{
		m_Qua = glm::qua<float>(glm::vec3(m_Pitch, m_Yaw, m_Roll));
	}
	ptt::SceneObj::SceneObj(SceneObj* parent , Sprite* sprite)
		:m_ParentObj(parent),
		m_Sprite(sprite),
		m_Yaw(0.0f),
		m_Pitch(0.0f),
		m_Roll(0.0f),
		m_ModelTrans(1.0f),
		m_Position(0.0f),
		m_Qua(glm::vec3(0.0f, 0.0f, 0.0f))
	{

		if (m_ParentObj != nullptr)
		{
			m_ParentObj->m_ChildObj.push_back(this);
		}
	}

	SceneObj::~SceneObj()
	{
		this->Clear();
	}

	void SceneObj::Update(float deltaTime)
	{
		for (SceneObj* child : m_ChildObj)
		{
			child->Update(deltaTime);
		}
		UpdateQuaternion();
	}

	void ptt::SceneObj::Render()
	{
		if (m_ParentObj)
			m_ModelTrans = m_ParentObj->m_ModelTrans;
		else
			m_ModelTrans = glm::mat4(1.0f);
		m_ModelTrans = glm::translate(m_ModelTrans, m_Position);
		// EulerTrans(m_ModelTrans, m_Yaw, m_Pitch, m_Roll);
		QuaternionRotate(m_ModelTrans, m_Qua);
		if (m_Sprite)
			m_Sprite->Render(m_ModelTrans);
		for (auto child : m_ChildObj)
		{
			child->Render();
		}
	}
	void SceneObj::PushChild(SceneObj* child)
	{
		ASSERT(child->m_ParentObj == nullptr);
		child->m_ParentObj = this;
		m_ChildObj.push_back(child);
	}
	const glm::vec3& SceneObj::GetPosition() const
	{
		return m_Position;
	}
	float SceneObj::GetYaw() const
	{
		return m_Yaw;
	}
	float SceneObj::GetPitch() const
	{
		return m_Pitch;
	}
	float SceneObj::GetRoll() const
	{
		return m_Roll;
	}
	Sprite* SceneObj::GetSprite() const
	{
		return m_Sprite.get();
	}
	void SceneObj::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}
	void SceneObj::SetYaw(float yaw)
	{
		m_Yaw = yaw;
	}
	void SceneObj::SetPitch(float pitch)
	{
		m_Pitch = pitch;
	}
	void SceneObj::SetRoll(float roll)
	{
		m_Roll = roll;
	}
	void SceneObj::SetEulerAngle(float yaw, float pitch, float roll)
	{
		m_Yaw = yaw;
		m_Pitch = pitch;
		m_Roll = roll;
	}
	void SceneObj::SetEulerAngle(float* eulerAngle)
	{
		m_Yaw = eulerAngle[0];
		m_Pitch = eulerAngle[1];
		m_Roll = eulerAngle[2];
	}
	void SceneObj::Move(const glm::vec3& vec)
	{
		m_Position += vec;
	}
	void SceneObj::EulerRotate(float yaw, float pitch, float roll)
	{
		m_Yaw += yaw;
		m_Pitch += pitch;
		m_Roll += roll;

	}
	void SceneObj::EulerRotateYaw(float yaw)
	{
		m_Yaw += yaw;
	}
	void SceneObj::EulerRotatePitch(float pitch)
	{
		m_Pitch += pitch;
	}
	void SceneObj::EulerRotateRoll(float roll)
	{
		m_Roll += roll;
	}
}