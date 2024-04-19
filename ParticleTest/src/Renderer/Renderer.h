#pragma once


namespace ptt
{
	class Renderer
	{
	protected:
		glm::mat4 m_ViewTrans;
		glm::mat4 m_ModelTrans;
		glm::mat4 m_ProjectionTrans;
	public:
		Renderer();
		virtual ~Renderer();
		
		virtual void SetTransMat();

		void SetViewTrans(const glm::mat4& viewTrans);
		void SetModelTrans(const glm::mat4& modelTrans);
		void SetProjectionTrans(const glm::mat4& projectionTrans);
	};
}