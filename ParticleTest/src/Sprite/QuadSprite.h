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
	class QuadSprite :public ColoredSprite<1>
	{
	protected:
		struct Texture
		{
			LM::Texture* m_Texture;
			float offsetx, offsety;
			float scalex, scaley;
			Texture(LM::Texture* tex) :
				m_Texture(tex), offsetx(0.0f), offsety(0.0f), scalex(1.0f), scaley(1.f)
			{}
		};

		LM::VertexArray m_vao;
		LM::VertexBuffer m_vbo;

		std::vector<Texture> m_Textures;
		
		virtual void Init();
		virtual void TextureSelector();
	public:
		QuadSprite(bool init = true);
		virtual ~QuadSprite();
		virtual void Render(const glm::mat4& modelTrans) override;
		virtual void RenderImGui() override;
	};
}