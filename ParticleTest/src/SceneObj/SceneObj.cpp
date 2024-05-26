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
	ptt::SceneObj::SceneObj(SceneObj* parent, Sprite* sprite, const std::string& objName)
		:m_ParentObj(parent), m_ObjName(objName),
		m_Sprite(sprite),
		m_Yaw(0.0f),
		m_Pitch(0.0f),
		m_Roll(0.0f),
		m_ModelTrans(1.0f),
		m_Position(0.0f),
		m_Scale(1.0f),
		m_Qua(glm::vec3(0.0f, 0.0f, 0.0f))
	{
		if (m_ParentObj != nullptr)
		{
			m_ParentObj->m_ChildObj.push_back(this);
		}
	}

	SceneObj::~SceneObj()
	{
		if (m_Sprite)
			delete m_Sprite;
		this->Clear();
	}

	void SceneObj::Update(float deltaTime)
	{
		for (SceneObj* child : m_ChildObj)
		{
			child->Update(deltaTime);
		}
		UpdateQuaternion();
		udSprite* sp = dynamic_cast<udSprite*>(m_Sprite);
		if (sp)
			sp->Update(deltaTime);
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
		m_ModelTrans = glm::scale(m_ModelTrans, m_Scale);
		if (m_Sprite && m_Sprite->IsVisible())
			Renderer::RenderSprite(m_Sprite, m_ModelTrans);
		for (auto child : m_ChildObj)
		{
			child->Render();
		}
	}
	void SceneObj::PushChild(SceneObj* child)
	{
		if (child->m_ParentObj)
			(child->m_ParentObj)->RemoveChild(child, true);
		child->m_ParentObj = this;
		m_ChildObj.push_back(child);
	}
	void SceneObj::RemoveChild(SceneObj* child, bool swap)
	{
		for (auto iter = m_ChildObj.begin(); iter != m_ChildObj.end(); iter++)
		{
			if (*iter == child)
			{
				if (!swap)
				{
					delete child;
				}
				m_ChildObj.erase(iter);
				return;
			}
		}
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
	const Sprite* SceneObj::GetSprite() const
	{
		return m_Sprite;
	}
	Sprite* SceneObj::GetSprite()
	{
		return m_Sprite;
	}
	bool SceneObj::HasChild() const
	{
		return !(m_ChildObj.empty());
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
	const glm::vec3& SceneObj::GetScale() const
	{
		return m_Scale;
	}
	void SceneObj::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
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
	void SceneObj::RenderImGui()
	{
		ImGui::SeparatorText("Object");
		ImGui::DragFloat3("Position", &m_Position.x, 0.1f);
		ImGui::Text("Rotate");
		ImGui::DragFloat("Pitch - xAxis", &m_Pitch,
			0.01f, -PI, PI, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat("Yaw - yAxis", &m_Yaw, 0.01f, -PI, PI, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat("Roll - zAxis", &m_Roll, 0.01f, -PI, PI, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat3("Scale", &m_Scale.x, 0.01f, 0.01f, 100.0f, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		if (m_Sprite)
		{
			if (ImGuiInterface* gui = dynamic_cast<ImGuiInterface*>(m_Sprite))
				gui->RenderImGui();
		}
	}
	const std::string& SceneObj::GetObjName() const
	{
		return m_ObjName;
	}
	const std::vector<SceneObj*> SceneObj::GetChildren() const
	{
		return m_ChildObj;
	}
	SceneObj* SceneObj::GetParent()
	{
		return m_ParentObj;
	}
}