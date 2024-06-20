#pragma once
#include "Sprite.h"
#include "glObj/VertexBuffers.h"
#include "VertexArray.h"
namespace ptt
{
	class CustomedSprite :public Sprite
	{
	public:
		struct Vertex
		{
			float x, y, z, r, g, b, a;
			Vertex(float xx, float yy, float zz)
				:x(xx), y(yy), z(zz)
			{
				r = g = b = a = 1.0f;
			}
			Vertex(float rr, float gg, float bb, float aa)
				:r(rr), g(gg), b(bb), a(aa)
			{
				x = y = z = 0.0f;
			}
			Vertex()
			{
				x = y = z = 0.0f;
				r = g = b = a = 1.0f;
			}
			Vertex(float xx, float yy, float zz, float rr, float gg, float bb, float aa)
				:x(xx), y(yy), z(zz), r(rr), g(gg), b(bb), a(aa)
			{
			}
		};
	protected:
		std::vector<Vertex> m_Vertices;
		GLenum m_Mode;
		VertexBuffers m_VertexBuffer;
		LM::VertexArray m_VertexArray;
		float m_VertexSize;

		int m_SelectedVertex;

		GLenum m_DrawModes[7];
		std::map<GLenum, std::string> m_NameMap;

		void Init();

	public:
		CustomedSprite();
		
		void UpdateVertexBuffer();

		virtual void Render(const glm::mat4& modelTrans) override;
		virtual void RenderImGui() override;

		void Update(float deltaTime) override;
		void AddVertex(Vertex vert);
	};
}