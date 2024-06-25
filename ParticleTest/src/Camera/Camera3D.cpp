#include"pch.h"
#include "Camera/Camera3D.h"
namespace ptt
{
	void Camera3D::UpdateDir()
	{
		static glm::vec3 origin(0.0f, 0.0f, -1.0f);
		static glm::mat4 trans(1.0f);
		trans = glm::rotate(glm::mat4(1.0f), m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));

		m_Front = trans * glm::vec4(origin,1.f);
		m_Front = glm::normalize(m_Front);

		trans = glm::rotate(trans, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::rotate(trans, m_fov, glm::vec3(0.0f, 0.0f, 1.0f));

		m_Dir = trans * glm::vec4(origin,1.0f);
		m_Right = glm::cross(m_Dir, m_Up);
		m_Dir = glm::normalize(m_Dir);
		m_Right = glm::normalize(m_Right);
	}
	void Camera3D::UpdateViewTrans()
	{
		m_ViewTrans = glm::lookAt(m_Pos, m_Pos + m_Dir, glm::vec3(0.0f, 1.0f,0.f));
	}
	void Camera3D::UpdateProjectionTrans()
	{
		switch (m_Projection)
		{
		case ptt::Camera3D::Ortho:
			m_ProjectionTrans = glm::ortho(-m_Width / 2, m_Width / 2, -m_Height / 2, m_Height / 2, m_Near, m_Far);
			break;
		case ptt::Camera3D::Perspective:
			m_ProjectionTrans = glm::perspective(m_ViewRange, m_Width / m_Height, m_Near, m_Far);
			break;
		default:
			m_ProjectionTrans = glm::perspective(m_ViewRange, m_Width / m_Height, m_Near, m_Far);
			break;
		}
		
	}
	void Camera3D::Move(float deltaTime)
	{
#ifdef IMPL_INPUT
		if (Input::IsKeyPressed(GLFW_KEY_A))
		{
			m_Pos -= deltaTime * m_SenPos * m_Right;
		}
		if (Input::IsKeyPressed(GLFW_KEY_D))
		{
			m_Pos += deltaTime * m_SenPos * m_Right;
		}
		if (Input::IsKeyPressed(GLFW_KEY_W))
		{
			m_Pos += deltaTime * m_SenPos * m_Front;
		}
		if (Input::IsKeyPressed(GLFW_KEY_S))
		{
			m_Pos -= deltaTime * m_SenPos * m_Front;
		}
		if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			m_Pos -= deltaTime * m_SenPos * m_Up;
		}
		if (Input::IsKeyPressed(GLFW_KEY_SPACE))
		{
			m_Pos += deltaTime * m_SenPos * m_Up;
		}
#endif
	}
	void Camera3D::Rotate(float deltaTime)
	{
#ifdef IMPL_INPUT
		if (Input::IsKeyPressed(GLFW_KEY_LEFT))
		{
			m_yaw += deltaTime * m_SenRad;
		}

		if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
		{
			m_yaw -= deltaTime * m_SenRad;
		}

		if (Input::IsKeyPressed(GLFW_KEY_DOWN))
		{
			m_pitch -= deltaTime * m_SenRad;
		}

		if (Input::IsKeyPressed(GLFW_KEY_UP))
		{
			m_pitch += deltaTime * m_SenRad;
		}

		if (m_pitch > 1.5f)
		{
			m_pitch = 1.5f;
		}
		if (m_pitch < -1.5f)
		{
			m_pitch = -1.5f;
		}
#endif
	}
	Camera3D::Camera3D()
		:m_Pos(0.0f, 0.0f, 0.0f),
		m_Dir(0.f, 0.0f, -1.0f),
		m_Up(0.0f, 1.0f, 0.0f),
		m_Right(1.0f, 0.0f, 0.0f),
		m_Front(0.f, 0.0f, -1.0f),
		m_yaw(0.0f),
		m_pitch(0.0f),
		m_fov(0.0f),
		m_ViewRange(PI/ 4),
		m_SenRad(PI / 4),
		m_SenPos(5.0f),
		m_Projection(Perspective)
	{
		m_Near = 0.1f;
		m_Far = 100.f;
	}
	Camera3D::~Camera3D()
	{
	}
	void Camera3D::Update(float deltaTime)
	{
		Move(deltaTime);
		Rotate(deltaTime);
		UpdateDir();
		UpdateProjectionTrans();
		UpdateViewTrans();
	}
	void Camera3D::SetRotationSensitivity(float sen)
	{
		m_SenRad = sen;
	}
	void Camera3D::SetMoveSensitivity(float sen)
	{
		m_SenPos = sen;
	}
	float Camera3D::GetViewRange() const
	{
		return m_ViewRange;
	}
	void Camera3D::SetViewRange(float rad)
	{
		rad = rad < 0.1f ? 0.1f : rad;
		rad = rad > 1.2f ? rad : 1.2f;
		m_ViewRange = rad;
	}
	const glm::vec3& Camera3D::GetPosition()
	{
		// TODO: insert return statement here
		return m_Pos;
	}
	const glm::vec3& Camera3D::GetAhead()
	{
		// TODO: insert return statement here
		return m_Dir;
	}
	void Camera3D::HeadTo(const glm::vec3& target)
	{
		glm::vec3 dir = target - m_Pos;
		float xz = sqrtf(dir.x * dir.x + dir.z * dir.z);
		if (xz > 0.0f)
		{
			m_yaw = dir.x > 0 ? -acosf(-dir.z / xz): acosf(-dir.z / xz);
		}

		float xyz = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		if (xyz > 0.0f)
		{
			m_pitch = acos(xz / xyz);
			m_pitch = dir.y > 0 ? m_pitch : -m_pitch;
			m_pitch = m_pitch < 1.5f ? m_pitch : 1.5f;
			m_pitch = m_pitch > -1.5f ? m_pitch : -1.5f;
		}
	}
	void Camera3D::SetPos(const glm::vec3& pos)
	{
		m_Pos = pos;
	}
	void Camera3D::SetYaw(float yaw)
	{
		m_yaw = yaw;
	}
	void Camera3D::SetPitch(float pitch)
	{
		m_pitch = pitch;
		m_pitch = m_pitch < 1.5f ? m_pitch : 1.5f;
		m_pitch = m_pitch > -1.5f ? m_pitch : -1.5f;
	}
	void Camera3D::SetFov(float fov)
	{
		m_fov = fov;
	}
	void Camera3D::SetEulerAngle(float pitch, float yaw, float fov)
	{
		m_pitch = pitch;
		m_yaw = yaw;
		m_fov = fov;
	}
	float Camera3D::GetYaw() const
	{
		return m_yaw;
	}
	float Camera3D::GetPitch() const
	{
		return m_pitch;
	}
	float Camera3D::GetFov() const
	{
		return m_fov;
	}
	void Camera3D::RotateYaw(float yaw)
	{
		m_yaw += yaw;
	}
	void Camera3D::RotatePitch(float pitch)
	{
		m_pitch += pitch;
		m_pitch = m_pitch < 1.5f ? m_pitch : 1.5f;
		m_pitch = m_pitch > -1.5f ? m_pitch : -1.5f;
	}
	void Camera3D::RotateFov(float fov)
	{
		m_fov += fov;
	}
	void Camera3D::SetOrthoProjection()
	{
		m_Projection = Ortho;
	}
	void Camera3D::SetPerspectiveProjection()
	{
		m_Projection = Perspective;
	}

	Camera3D::Projection Camera3D::GetProjectionType() const
	{
		return m_Projection;
	}
}