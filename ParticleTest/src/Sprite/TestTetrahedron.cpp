#include "pch.h"
#include "TestTetrahedron.h"
namespace ptt
{
	void TestTetrahedron::Init()
	{
		float sqrt6 = 2.4495f;
		float sqrt2 = 1.4142f;
		float sqrt3 = 1.7321f;

		float vertices[]
		{
			// 位置									法线				纹理坐标
			0.0f,	sqrt6 / 2,	0.0f,				0.0f, 0.0f, 0.0f,	0.5f, 0.0f,
			0.0f,	-sqrt6 / 6,	-2 * sqrt3 / 3,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
			1.0f,	-sqrt6 / 6, sqrt3 / 3,			0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			-1.0f,	-sqrt6 / 6, sqrt3 / 3,			0.0f, 0.0f, 0.0f,	1.0f, 1.0f
		};
		unsigned int indices[]
		{
			0, 1, 2, 3, 0, 1
		};

		m_ShaderName = LM::Shaders::Mesh_P_N_T;
		m_VBO.Init(sizeof(vertices), vertices, GL_STATIC_DRAW);
		m_EBO.Init(6, indices, GL_STATIC_DRAW);
		m_VAO.SetMetaType(GL_TRIANGLE_STRIP);
		m_VAO.SetCount(6);
		m_VAO.SetEB(m_EBO.GetID());
		m_VAO.SetVB(m_VBO.GetID());
		m_VAO.PushAttrib<float>(3);
		m_VAO.PushAttrib<float>(3);
		m_VAO.PushAttrib<float>(2);
		m_VAO.ApplyLayout();
	}
	TestTetrahedron::TestTetrahedron()
		:TestCube(false)
	{
		Init();
	}
	void TestTetrahedron::Render(const glm::mat4& modelTrans)
	{
		const CameraObj* camera = Renderer::GetCurrentCamera();
		if (camera == nullptr)
			return;
		SelectShader();
		if (m_Shader == nullptr)
			return;

		m_Shader->Bind();
		SetUniformMaterial(m_Shader);

		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		mvpTrans = camera->GetProjectionTrans() * camera->GetViewTrans() * modelTrans;
		m_Shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		m_Shader->SetUniform4f("u_Color", &m_Color[0].r);
		
		m_VAO.DrawElement();
	}
}