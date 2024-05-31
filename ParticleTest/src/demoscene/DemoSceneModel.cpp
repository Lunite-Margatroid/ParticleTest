#include "pch.h"
#include "DemoSceneUI.h"
#include "DemoSceneModel.h"

namespace ptt
{
	void DemoSceneModel::Init()
	{
		m_SelectedObj = m_RootObj.get();
		// LoadModel("L:/OpenGL/model/nanosuit/nanosuit.blend");
		SceneObj* obj = new SceneObj(m_RootObj.get(), new QuadMeshSprite(), "mesh");

		m_Camera = Renderer::GetCamera(Renderer::Cameras::Camera3D_Alpha);
		Renderer::SetCurrentCamera(m_Camera);
	}
	ptt::DemoSceneModel::DemoSceneModel()
		:DemoSceneUI(false)
	{
		m_Materials.push_back(new Material());
		m_ModelCount = 0;
		Init();
	}

	DemoSceneModel::~DemoSceneModel()
	{
		for (Mesh* mesh : m_Meshes)
		{
			delete mesh;
		}
		for (Material* material : m_Materials)
		{
			delete material;
		}
	}

	void DemoSceneModel::LoadModel(const std::string& path)
	{
		Assimp::Importer fileImporter;

		const aiScene* scene = fileImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		/*
		aiProcess_Triangulate		转换成三角形
		aiProcess_FlipUVs			反转图片y轴
		*/

		// 查错
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::Assimp::" << fileImporter.GetErrorString() << std::endl;
			return;
		}


		// 获取路径
		std::string directory = path.substr(0, path.find_last_of('/'));
		directory = directory.substr(0, path.find_last_of('\\'));

		// material
		unsigned int materialBase = LoadMaterials(scene, directory);
		// meshed
		unsigned int meshBase = ProcessMeshes(scene, materialBase);

		m_ModelCount += 1;
		char num[16];
		itoa(m_ModelCount, num, 10);
		char objName[32] = "Model";
		strcat(objName, num);
		ModelObj* obj = new ModelObj(m_SelectedObj, nullptr, objName);
		obj->LoadModel(scene->mRootNode, meshBase);
	}


	void DemoSceneModel::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh* pttMesh = new Mesh();
			ProcessMesh(mesh, scene, pttMesh);
			m_Meshes.push_back(pttMesh);
		}
	}

	void DemoSceneModel::ProcessMesh(aiMesh* mesh, const aiScene* scene, Mesh* pttMesh)
	{
		// position		float3
		// normal		float3
		// texCoord		float2
		// tangent		float3
		size_t vertexCount = 11 * mesh->mNumVertices;
		float* vertice = new float[vertexCount];
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			float* temp = vertice + 11 * i;
			// position
			temp[0] = mesh->mVertices[i].x;
			temp[1] = mesh->mVertices[i].y;
			temp[2] = mesh->mVertices[i].z;

			// normal
			if (mesh->HasNormals())
			{
				temp[3] = mesh->mNormals[i].x;
				temp[4] = mesh->mNormals[i].y;
				temp[5] = mesh->mNormals[i].z;
			}
			else
			{
				memset(temp + 3, 0, sizeof(float) * 3);
			}
			// texCoord
			if (mesh->mTextureCoords[0])
			{
				temp[6] = mesh->mTextureCoords[0][i].x;
				temp[7] = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				temp[6] = temp[7] = 0.0f;
			}
			// tangent
			if (mesh->HasTangentsAndBitangents())
			{
				temp[8] = mesh->mTangents[i].x;
				temp[9] = mesh->mTangents[i].y;
				temp[10] = mesh->mTangents[i].z;
			}
		}
		unsigned int* element;
		size_t elementCount = 0;
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			elementCount += face.mNumIndices;
		}
		element = new unsigned int[elementCount];
		size_t p = 0;
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& face = mesh->mFaces[i];
			memcpy(element + p, face.mIndices, face.mNumIndices * sizeof(unsigned int));
			p += face.mNumIndices;
		}

		pttMesh->Init(vertice, vertexCount * sizeof(float), element, elementCount, nullptr);

		delete[] vertice;
		delete[] element;
	}

	unsigned int DemoSceneModel::ProcessMeshes(const aiScene* scene, unsigned int materialBase)
	{
		unsigned int offset = m_Meshes.size();
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* msh = scene->mMeshes[i];
			Mesh* mesh = new Mesh();
			ProcessMesh(msh, scene, mesh);
			mesh->SetMaterial(m_Materials[materialBase + msh->mMaterialIndex]);
			m_Meshes.push_back(mesh);
		}
		return offset;
	}

	void DemoSceneModel::LoadMeshes(const aiScene* scene)
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{

		}
	}

	unsigned int DemoSceneModel::LoadMaterials(const aiScene* scene, const std::string& directionary)
	{
		aiTextureType texTypes[4] = {aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_NORMALS, aiTextureType_HEIGHT};
		LM::TextureType lmTypes[4] = {LM::texture_diffuse, LM::texture_specular, LM::texture_normal, LM::texture_parallax};
		unsigned int ret = m_Materials.size();
		for (unsigned int i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* mtl = scene->mMaterials[i];
			Material* material = new Material();
			m_Materials.push_back(material);
			for (int j = 0; j < 4; j++)
			{
				if (mtl->GetTextureCount(texTypes[j]) > 0)
				{
					aiString str;
					mtl->GetTexture(texTypes[j], 0, &str);
					int begin = 0;
					const char* ch = str.C_Str();
					for (int i = 0; ch[i] != '\0'; i++)
					{
						if (ch[i] == '\\' || ch[i] == '/')
						{
							begin = i;
						}
					}
					std::string file(ch + begin);
					file = directionary + file;

					material->SetTexture(lmTypes[j], Renderer::LoadTexture(file, lmTypes[j], true));
				}
			}
		}
		return ret;
	}

	std::vector<Mesh*>& DemoSceneModel::GetMeshes()
	{
		// TODO: insert return statement here
		return m_Meshes;
	}

}