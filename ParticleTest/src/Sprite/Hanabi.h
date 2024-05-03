#pragma once
#include "ColoredSprite.h"
#include "Interface/ImGuiInterface.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

namespace ptt
{
	class Hanabi :public ColoredSprite<1>, public ImGuiInterface
	{
	protected:
		
		float m_VelHanabi[2];	// �ٶȵľ�ֵ�ͱ�׼��
		float m_VelSpark[2];	// �����ٶȵľ�ֵ�ͱ�׼��

		float m_TimeHanabi[2];	// ����ʱ�� 
		float m_TimeSpark[2];	// ���Ǵ���ʱ��ľ�ֵ�ͱ�׼��

		float m_kDF;			// ����ϵ��
		float m_kSparkDF;		// ���ǵ�����ϵ��

		glm::vec3 m_Acc;
		glm::vec3 m_SparkAcc;

		float m_DeltaTime;

		LM::VertexArray m_VAO[2];
		LM::VertexArray m_vaoSpark[2];

		LM::VertexBuffer m_Buffer[2];
		LM::VertexBuffer m_vbSpark[2];


	public:

	
	};
}