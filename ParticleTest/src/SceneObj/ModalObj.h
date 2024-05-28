#pragma once
#include "SceneObj.h"

namespace ptt
{
	class ModalObj : public SceneObj
	{
		// 模型文件的文件夹
		std::string m_Directory;
	public:
		ModalObj(SceneObj* parent = nullptr, Sprite* sprite = nullptr, const std::string& objName = "No Name");

		void LoadModal(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}