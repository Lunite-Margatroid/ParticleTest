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
		
		float m_VelHanabi[2];	// 速度的均值和标准差
		float m_VelSpark[2];	// 火星速度的均值和标准差

		float m_TimeHanabi[2];	// 存在时间 
		float m_TimeSpark[2];	// 火星存在时间的均值和标准差

		float m_kDF;			// 阻力系数
		float m_kSparkDF;		// 火星的阻力系数

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