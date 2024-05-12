#pragma once
#include "Sprite.h"
#include "ColoredSprite.h"
#include "Interface/ImGuiInterface.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera3D.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	class QuadSprite :public ColoredSprite<1>, public ImGuiInterface
	{
	protected:
		LM::VertexArray m_vao;
		LM::VertexBuffer m_vbo;

		void Init();
	public:
		QuadSprite();
		virtual ~QuadSprite();
		virtual void Render(const glm::mat4& modelTrans) override;
		virtual void RenderImGui() override;
	};
}