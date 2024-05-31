#include "pch.h"
#include "Mesh.h"
namespace ptt
{
	Mesh::Mesh(float* vertice, size_t verticeBufferSize, unsigned int* indice, size_t indexCount, Material* material)
	{
		Init(vertice, verticeBufferSize, indice, indexCount, material);
	}
	Mesh::Mesh()
		:m_Material(nullptr)
	{
	}
	Mesh::~Mesh()
	{
	}
	void Mesh::Init(float* vertice, size_t verticeBufferSize, unsigned int* indice, size_t indexCount, Material* material)
	{
		m_VBO.Init(verticeBufferSize, vertice, GL_STATIC_DRAW);
		m_EBO.Init(indexCount, indice, GL_STATIC_DRAW);

		m_VAO.SetMetaType(GL_TRIANGLES);
		m_VAO.SetCount(indexCount);
		m_VAO.PushAttrib<float>(3);	// postion float3
		m_VAO.PushAttrib<float>(3);	// normal float3
		m_VAO.PushAttrib<float>(2);	// texCoord float2
		m_VAO.PushAttrib<float>(3);	// tangent float3
		m_VAO.ApplyLayout();

		m_Material = material;

	}
	void Mesh::Render(LM::Shader* shader)
	{
		m_Material->SetUniformMaterial(shader);
		m_VAO.DrawElement();
	}
	void Mesh::SetMaterial(Material* material)
	{
		m_Material = material;
	}
}