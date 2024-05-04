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

		float m_VelHanabi[2];	// 烟花速度的均值和标准差
		float m_VelSpark[2];	// 火星速度的均值和标准差

		float m_TimeHanabi[2];	// 烟花存在时间 
		float m_TimeSpark[2];	// 火星存在时间的均值和标准差

		float m_kDF;			// 烟花的阻力系数
		float m_kSparkDF;		// 火星的阻力系数

		glm::vec3 m_Acc;		// 烟花的重力加速度
		glm::vec3 m_SparkAcc;	// 火星的重力加速度
		
		float m_DeltaTime;		// 帧时间

		LM::VertexArray m_VAO[2];		// 烟花vao
		LM::VertexArray m_vaoSpark[2];	// 火星vao

		LM::VertexBuffer m_Buffer[2];	// 烟花buffer
		LM::VertexBuffer m_vbSpark[2];	// 火星buffer

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