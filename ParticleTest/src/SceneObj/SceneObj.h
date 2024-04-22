#pragma once
#include "Sprite/Sprite.h"

namespace ptt
{
	class SceneObj
	{
	protected:
		SceneObj* m_ParentObj;
		std::unique_ptr<Sprite> m_Sprite;
		std::vector<SceneObj*> m_ChildObj;
		glm::vec3 m_Position;
		float m_Yaw;
		float m_Pitch;
		float m_Roll;

		glm::mat4 m_ModelTrans;

		void Clear();
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
		inline static void EulerTrans(glm::mat4& modelTrans, float* rad)
		{
			EulerTrans(modelTrans, rad[0], rad[1], rad[2]);
		}

		void PushChild(SceneObj* child);

		const glm::vec3& GetPosition() const;
		float GetYaw() const;
		float GetPitch() const;
		float GetRoll() const;
		Sprite* GetSprite()const;

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