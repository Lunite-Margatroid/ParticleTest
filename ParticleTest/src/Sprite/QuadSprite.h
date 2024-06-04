#pragma once
#include "Sprite.h"
#include "ColoredSprite.h"
#include "Interface/ImGuiInterface.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera3D.h"
#include "Material/Material.h"

namespace ptt
{
	class QuadSprite :public ColoredSprite<1>,virtual public Material
	{
	protected:
		LM::VertexArray* m_vao;
		
		virtual void Init();
		//virtual void TextureSelector();
	public:
		QuadSprite(bool init = true);
		virtual ~QuadSprite();
		virtual void Render(const glm::mat4& modelTrans) override;
		virtual void RenderImGui() override;

		virtual void SelectShader() override;
	};
}