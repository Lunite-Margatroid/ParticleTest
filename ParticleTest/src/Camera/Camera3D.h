#pragma once
#include "Camera/Camera.h"



namespace ptt
{
	class Camera3D :public Camera
	{
	public:
		enum Projection
		{
			Ortho, Perspective
		};
	protected:
		glm::vec3 m_Pos;			// camera position
		glm::vec3 m_Dir;			// view ahead
		glm::vec3 m_Up;				// up for move
		glm::vec3 m_Right;			// right for move
		glm::vec3 m_Front;			// front for move
		
		float m_yaw;				// ת��Ϊy�� ����
		float m_pitch;				// ת��Ϊx�� ����

		float m_fov;				// ת��Ϊz�� Roll

		float m_ViewRange;			// ��Ұ�Ƕ�
		
		float m_SenRad;				// Sensitivity Of rotate
		float m_SenPos;				// Sensitivity Of Move

		Projection m_Projection;


		void UpdateDir();
		virtual void UpdateViewTrans() override;
		virtual void UpdateProjectionTrans() override;
		virtual void Move(float deltaTime);
		virtual void Rotate(float deltaTime);
	public:
		Camera3D();
		virtual ~Camera3D();

		virtual void Update(float deltaTime) override;

		void SetRotationSensitivity(float sen);
		void SetMoveSensitivity(float sen);

		float GetViewRange() const;
		void SetViewRange(float);

		const glm::vec3& GetPosition();
		const glm::vec3& GetAhead();

		void HeadTo(const glm::vec3& target);

		void SetPos(const glm::vec3& pos);
		void SetYaw(float yaw);
		void SetPitch(float pitch);
		void SetFov(float fov);
		void SetEulerAngle(float pitch, float yaw, float fov);

		float GetYaw() const;
		float GetPitch() const;
		float GetFov() const;

		void RotateYaw(float yaw);
		void RotatePitch(float pitch);
		void RotateFov(float fov);

		void SetOrthoProjection();
		void SetPerspectiveProjection();

		Projection GetProjectionType() const;
	};
}