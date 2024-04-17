#pragma once
#include "DemoScene.h"
#include "Shader.h"
#include "Camera3D.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
namespace ptt
{
	class QuadMeshScene :public DemoScene
	{
	protected:
		LM::Shader m_Shader;
		Camera3D m_Camera;

		LM::VertexBuffer m_Buffer;
		LM::VertexArray m_VAO;

		glm::vec4 m_MeshColor;

		void Init();

		void SetUnifrom();
	public:
		QuadMeshScene();
		virtual ~QuadMeshScene();

		void Render() override;
		void Update(float deltaTime) override;
		void RenderImGui() override;
		

	};
}