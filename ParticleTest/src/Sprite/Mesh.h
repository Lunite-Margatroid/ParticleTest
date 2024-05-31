#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Material/Material.h"
#include "Shader/Shader.h"
namespace ptt
{
	class Mesh
	{
	protected:
		LM::VertexBuffer m_VBO;
		LM::ElementBuffer m_EBO;
		LM::VertexArray m_VAO;

		Material* m_Material;

	public:
		Mesh(float* vertice, size_t verticeBufferSize, unsigned int* indice, size_t indexCount, Material* material);
		Mesh();
		virtual ~Mesh();
		void Init(float *vertice, size_t verticeBufferSize, unsigned int* indice, size_t indexCount, Material* material);

		virtual void Render(LM::Shader* shader);
		void SetMaterial(Material* material);
	};
}