#pragma once
#include "ColoredSprite.h"
#include "Interface/ImGuiInterface.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "udSprite.h"
#include "Rand/Rand.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	class Hanabi :public ColoredSprite<1>, public ImGuiInterface, public udSprite
	{
	public:
		enum class Distribution { random, uniform };
	protected:
		
		const unsigned int m_Count;
		const unsigned int m_SparkCount;

		float m_VelHanabi[2];	// �̻��ٶȵľ�ֵ�ͱ�׼��
		float m_VelSpark[2];	// �����ٶȵľ�ֵ�ͱ�׼��

		float m_TimeHanabi[2];	// �̻�����ʱ�� 
		float m_TimeSpark[2];	// ���Ǵ���ʱ��ľ�ֵ�ͱ�׼��

		float m_kDF;			// �̻�������ϵ��
		float m_kSparkDF;		// ���ǵ�����ϵ��

		glm::vec3 m_Acc;		// �̻����������ٶ�
		glm::vec3 m_SparkAcc;	// ���ǵ��������ٶ�
		
		float m_DeltaTime;		// ֡ʱ��

		LM::VertexArray m_VAO[2];		// �̻�vao
		LM::VertexArray m_vaoSpark[2];	// ����vao

		LM::VertexBuffer m_Buffer[2];	// �̻�buffer
		LM::VertexBuffer m_vbSpark[2];	// ����buffer

		Distribution m_Distribution;
		Distribution m_sparkDistribution;

		float m_HanabiSize;
		float m_SparkSize;

		bool m_BufferFlag;

		void Init();
		void GenData(float*);

	public:
		Hanabi(unsigned int count = 100, unsigned int sparkCount = 50);
		virtual ~Hanabi();
		
		virtual void Update(float deltaTime) override;
		virtual void Render(const glm::mat4& modelTrans) override;
		void RenderImGui() override;
		void Reset();
	};
}