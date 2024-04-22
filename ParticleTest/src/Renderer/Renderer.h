#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Camera3D.h"
namespace ptt
{
	class Renderer
	{
	protected:
		glm::mat4 m_ViewTrans;
		glm::mat4 m_ModelTrans;
		glm::mat4 m_ProjectionTrans;

		LM::Shader* m_CurrentShader;
		Camera* m_CurrentCamera;
		Renderer();

		static Renderer* s_Instance;
	public:
		virtual ~Renderer();
		
		virtual void SetTransMat();

		void SetViewTrans(const glm::mat4& viewTrans);
		void SetModelTrans(const glm::mat4& modelTrans);
		void SetProjectionTrans(const glm::mat4& projectionTrans);

		static void SetCurrentShader(LM::Shader* shader);
		static void SetCurrentCamera(Camera* camera);

		static Renderer* GetInstance();

		static LM::Shader* GetCurrentShader();
		static Camera* GetCurrentCamera();
	};
}