#pragma once
#include "DemoSceneUI.h"
#include "Sprite/Mesh.h"
#include "glObj/VertexBuffers.h"
#include "SceneObj/ModelObj.h"
#include "Sprite/SkyboxSprite.h"

namespace ptt
{
	class DemoSceneModel : public DemoSceneUI
	{
	protected:
		std::vector<Mesh*> m_Meshes;
		std::vector<Material*> m_Materials;		// 本类析构	0为默认材质
		std::vector<LM::Texture*> m_Textures;	// 析构时不需要delete Renderer的析构函数delete

		unsigned int m_ModelCount;

		virtual void Init();
	public:

		DemoSceneModel();
		~DemoSceneModel();

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, Mesh* pttMesh);
		unsigned int ProcessMeshes(const aiScene* scene, unsigned int materialBase);

		void LoadMeshes(const aiScene* scene);
		unsigned int LoadMaterials(const aiScene* scene, const std::string& directionary);

		std::vector<Mesh*>& GetMeshes();
	};
}