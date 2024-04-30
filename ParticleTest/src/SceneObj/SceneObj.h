#pragma once
#include "Sprite/Sprite.h"
#include "Sprite/udSprite.h"
namespace ptt
{
	class SceneObj
	{
	protected:
		SceneObj* m_ParentObj;
		Sprite* m_Sprite;
		std::vector<SceneObj*> m_ChildObj;
		glm::vec3 m_Position;
		float m_Yaw;
		float m_Pitch;
		float m_Roll;

		glm::mat4 m_ModelTrans;
		glm::qua<float> m_Qua;

		void Clear();
		void UpdateQuaternion();
	public:
		SceneObj(SceneObj* parent = nullptr, Sprite* sprite = nullptr);
		virtual ~SceneObj();

		virtual void Update(float deltaTime);
		virtual void Render();

		inline static void EulerTrans(glm::mat4& modelTrans, float yaw, float pitch, float roll)
		{
			modelTrans = glm::rotate(modelTrans, roll, glm::vec3(0.0f, 0.0f, 1.0f));
			modelTrans = glm::rotate(modelTrans, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
			modelTrans = glm::rotate(modelTrans, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		inline static void EulerTrans(glm::mat4& modelTrans, const float* rad)
		{
			EulerTrans(modelTrans, rad[0], rad[1], rad[2]);
		}

		inline static void QuaternionRotate(glm::mat4& modelTrans, const glm::qua<float>& qua)
		{
			glm::vec3 axis = glm::axis(qua);
			float angle = glm::angle(qua);
			modelTrans = glm::rotate(modelTrans, angle, axis);
		}

		void PushChild(SceneObj* child);

		const glm::vec3& GetPosition() const;
		float GetYaw() const;
		float GetPitch() const;
		float GetRoll() const;
		const Sprite* GetSprite()const;
		Sprite* GetSprite();

		void SetPosition(const glm::vec3& position);
		void SetYaw(float yaw);
		void SetPitch(float pitch);
		void SetRoll(float roll);
		void SetEulerAngle(float yaw, float pitch, float roll);
		void SetEulerAngle(float* eulerAngle);

		void Move(const glm::vec3& vec);
		void EulerRotate(float yaw, float pitch, float roll);
		void EulerRotateYaw(float yaw);
		void EulerRotatePitch(float pitch);
		void EulerRotateRoll(float roll);
	};
}