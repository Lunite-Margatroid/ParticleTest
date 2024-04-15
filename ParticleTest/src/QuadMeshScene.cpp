#include "pch.h"
#include "QuadMeshScene.h"

namespace ptt
{
	void QuadMeshScene::Init()
	{
		const float tt = 100.0f;
		float vertice[] =
		{
			// x      z
			-tt, -tt,
			-tt, tt,
			tt, tt,
			tt, -tt
		};

		m_Buffer.Init(sizeof(vertice), vertice, GL_STATIC_DRAW);
		m_VAO.SetVB(m_Buffer.GetID());
		m_VAO.PushAttrib<float>(2);
		m_VAO.ApplyLayout();
		m_VAO.SetMetaType(GL_TRIANGLE_FAN);
	}
	void QuadMeshScene::SetUnifrom()
	{
		static glm::mat4 vpTrans;
		const glm::mat4& viewTrans = m_Camera.GetViewTrans();
		const glm::mat4& projectionTrans = m_Camera.GetProjectionTrans();
		vpTrans =  projectionTrans * viewTrans;
		m_Shader.Bind();
		m_Shader.SetUniformMatrix4f("u_VPTrans", false, glm::value_ptr(vpTrans));
		m_Shader.SetUniform4f("u_MeshColor", m_MeshColor.r, m_MeshColor.g, m_MeshColor.b, m_MeshColor.a);
	}
	QuadMeshScene::QuadMeshScene()
		:m_Shader("./res/shader/QuadMeshVertex.shader", "./res/shader/QuadMeshFrag.shader"),
		m_MeshColor(1.0f)
	{
		Init();
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
	QuadMeshScene::~QuadMeshScene()
	{
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glDisable(GL_BLEND));
	}
	void QuadMeshScene::Render()
	{
		GLCall(glClear(GL_DEPTH_BUFFER_BIT));
		SetUnifrom();
		m_VAO.DrawArray(4);
	}
	void QuadMeshScene::Update(float deltaTime)
	{
		m_Camera.Update(deltaTime);
	}

	void QuadMeshScene::RenderImGui()
	{
		const glm::vec3& cameraPos = m_Camera.GetPosition();
		const glm::vec3& cameraAhead = m_Camera.GetAhead();

		ImGui::Text("CameraPos: %.2f  %.2f  %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
		ImGui::Text("CameraAhead: %.2f  %.2f  %.2f", cameraAhead.x, cameraAhead.y, cameraAhead.z);
	}
}