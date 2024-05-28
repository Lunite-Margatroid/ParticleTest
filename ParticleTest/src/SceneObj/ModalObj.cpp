#include "pch.h"
#include "ModalObj.h"

namespace ptt
{
	ModalObj::ModalObj(SceneObj* parent, Sprite* sprite, const std::string& objName)
		:SceneObj(parent, sprite, objName)
	{
	}
	void ModalObj::LoadModal(const std::string& path)
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
		m_Directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}
	void ModalObj::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}
	}

	void ModalObj::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		// position		float3
		// normal		float3
		// texCoord		float2
		// tangent		float3
		float* vertice = new float[11 * mesh->mNumVertices];
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
				memset(temp+ 3, 0, sizeof(float) * 3);
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


		delete[] vertice;
		delete[] element;
	}


}