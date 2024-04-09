#pragma once
#include "Input.h";

#ifndef PI
#define PI 3.14159f
#else

#endif

namespace ptt
{
	class Camera
	{
	protected:
		mutable glm::mat4 m_ViewTrans;
		mutable glm::mat4 m_ProjectionTrans;

		float m_Width;
		float m_Height;

		float m_Near, m_Far;

		virtual void UpdateViewTrans() =0;
		virtual void UpdateProjectionTrans() =0 ;
	public:
		Camera();
		virtual ~Camera();
		const glm::mat4& GetViewTrans() const;
		const glm::mat4& GetProjectionTrans() const;

		virtual void Update(float deltaTime) = 0;

		void SetNear(float near);
		void SetFar(float far);

		void SetWidth(float width);
		void SetHeight(float height);

	};
}