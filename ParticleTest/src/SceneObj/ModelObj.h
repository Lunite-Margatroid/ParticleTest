#pragma once
#include "SceneObj.h"
#include "Sprite/Mesh.h"
#include "Sprite/SpriteMeshes.h"

namespace ptt
{
	class ModelObj : public SceneObj
	{
	protected:

	public:
		ModelObj(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void LoadModel(aiNode* root, unsigned int meshBase);
	};
}