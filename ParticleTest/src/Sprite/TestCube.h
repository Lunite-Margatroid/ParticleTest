#pragma once
#include "ColoredSprite.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Material/Material.h"

namespace ptt
{
	class TestCube : public ColoredSprite<1>, virtual public Material
	{
	protected:
		LM::VertexBuffer m_VBO;
		LM::ElementBuffer m_EBO;
		LM::VertexArray m_VAO;

		void Init();
	public:
		TestCube();
		TestCube(bool init);

		void Render(const glm::mat4& modelTrans) override;
		void RenderImGui() override;
	};
}