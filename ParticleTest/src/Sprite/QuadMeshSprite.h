#pragma once
#include "Sprite.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	class QuadMeshSprite :public Sprite
	{
	private:
		LM::VertexBuffer m_Buffer;
		LM::VertexArray m_VAO;

		glm::vec4 m_MeshColor;

		void Init();
	public:
		QuadMeshSprite();
		~QuadMeshSprite();

		void SetMeshColor(const glm::vec4& color);

		virtual void Render(const glm::mat4& modelTrans) override;
	};
}