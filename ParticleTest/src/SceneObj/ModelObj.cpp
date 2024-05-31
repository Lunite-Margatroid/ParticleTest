#include "pch.h"
#include "ModelObj.h"
#include "demoscene/DemoSceneModel.h"
#include "Application.h"
namespace ptt
{
	ModelObj::ModelObj(SceneObj* parent, Sprite* sprite, const std::string& objName)
		:SceneObj(parent, sprite, objName)
	{
	}

	void ModelObj::LoadModel(aiNode* root, unsigned int meshBase)
	{
		DemoSceneModel* scene = dynamic_cast<DemoSceneModel*>(Application::GetCurrentScene());
		
		if (scene)
		{
			SpriteMeshes* sprite = new SpriteMeshes();
			std::vector<Mesh*>& meshes = scene->GetMeshes();

			for (unsigned int i = 0; i < root->mNumMeshes; i++)
			{
				sprite->PushMeshBack(meshes[root->mMeshes[i] + meshBase]);
			}
			m_Sprite = sprite;

			for (int i = 0; i < root->mNumChildren; i++)
			{
				char temp[32] = "child_";
				char num[16];
				itoa(i + 1, num, 10);
				strcat(temp, num);
				ModelObj* obj = new ModelObj(this, nullptr, temp);
				obj->LoadModel(root->mChildren[i], meshBase);
			}
		}
	}
	

}