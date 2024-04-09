#pragma once
#include "DemoScene.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Feedback.h"
#include "Camera.h"
#include "Camera3D.h"
#include "tfBuffer.h"
namespace ptt
{
	class SinWave :public DemoScene
	{
	private:
		LM::Shader m_Shader;
		LM::tfBuffer m_VB1;
		LM::tfBuffer m_VB2;
		LM::VertexArray m_VA1;
		LM::VertexArray m_VA2;
		Feedback m_Feedback;
		int m_VerticeNum;

		Camera3D m_Camera;
		float m_DeltaTime;


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