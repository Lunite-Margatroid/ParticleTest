#pragma once
#include "Sprite.h"
#include "Mesh.h"
#include "ColoredSprite.h"

namespace ptt
{
	class SpriteMeshes : virtual public Sprite,public ColoredSprite<1>
	{
	protected:
		std::vector<Mesh*> m_Meshes;
	public:
		SpriteMeshes();

		void PushMeshBack(Mesh* mesh);

		virtual void Render(const glm::mat4& modelTrans) override;
		virtual void SelectShader() override;
		virtual void RenderImGui() override;
	};
}