#pragma once
#include "DemoScene.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Feedback.h"
#include "Camera.h"
#include "Camera3D.h"
namespace ptt
{
	class SinWave :public DemoScene
	{
	private:
		LM::Shader m_Shader;
		LM::VertexBuffer m_VB;
		LM::VertexArray m_VA;
		Feedback m_Feedback;
		int m_VerticeNum;

		Camera3D m_Camera;

		void InitVertexBuffer();
		void InitVertexArray();
		void InitFeedback();
		void Init();

		void SetShaderUniform();

	public:
		SinWave();
		~SinWave();


		void Render() override;
		void Update(float deltaTime) override;
	};
}