#pragma once
#include "DemoSceneUI.h"
#include "Sprite/Mesh.h"
#include "glObj/VertexBuffers.h"
#include "SceneObj/ModelObj.h"
#include "Sprite/SkyboxSprite.h"
#include "Sprite/CustomedSprite.h"
#include "Sprite/FireWork.h"

namespace ptt
{
	class DemoSceneModel : public DemoSceneUI
	{
	public:
		enum class SpriteType
		{
			Quad, Cube, Sphere, Skybox, Custom, Firework, Hanabi, QuadMesh
		};
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


		void AddSceneObject(SpriteType spriteType, const std::string& objName);

		template<typename TOnject, typename TSprite>
		void AddSceneObject(const std::string& ObjectName)
		{
			ASSERT(false);
		}

		template<>
		void AddSceneObject<SceneObj, QuadMeshSprite>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new QuadMeshSprite(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, QuadSprite>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new QuadSprite(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, CustomedSprite>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new CustomedSprite(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, FireWork>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new FireWork(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, Hanabi>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new Hanabi(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, CubeSprite>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new CubeSprite(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, SphereSprite>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new SphereSprite(), ObjectName);
		}

		template<>
		void AddSceneObject<SceneObj, SkyboxSprite>(const std::string& ObjectName)
		{
			SceneObj* obj = new SceneObj(m_SelectedObj, new SkyboxSprite(), ObjectName);
		}

	};
}