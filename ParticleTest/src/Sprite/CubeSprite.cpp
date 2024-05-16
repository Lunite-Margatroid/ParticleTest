#include "pch.h"
#include "CubeSprite.h"

namespace ptt
{
	void CubeSprite::Init()
	{
		unsigned int indices[] =
		{
		0, 1,2,0,2,3,		
		4,5,6, 4,6,7,		
		8,9,10,8,10,11,		
		12,13,14,12,14,15,	
		16,17,18,16,18,19,	
		20, 21,22,20,22,23 };
		float vertices[] =
		{
			// 位置坐标					法线向量					纹理坐标
			-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			0.0f, 0.0f,
			1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			0.0f, 1.0f,

			-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,			0.0f, 0.0f,
			-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			1.0f, 0.0f,
			1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			0.0f, 1.0f,

			-1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,			0.0f, 0.0f,
			-1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,			1.0f, 0.0f,
			1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,			1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,			0.0f, 1.0f,

			-1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,			0.0f, 0.0f,
			1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,			1.0f, 0.0f,
			1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,			1.0f, 1.0f,
			-1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,			0.0f, 1.0f,

			1.0f,-1.0f, -1.0f,		1.0f, 0.0f,  0.0f,			0.0f, 0.0f,
			1.0f,1.0f, -1.0f,		1.0f, 0.0f,  0.0f,			1.0f, 0.0f,
			1.0f,1.0f, 1.0f,		1.0f, 0.0f,  0.0f,			1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,		1.0f, 0.0f,  0.0f,			0.0f, 1.0f,

			-1.0f,-1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,			0.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,			1.0f, 0.0f,
			-1.0f,1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,			1.0f, 1.0f,
			-1.0f,1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,			0.0f, 1.0f
		};
		m_vbo.Init(sizeof(vertices), vertices);
		m_ebo.Init(36, indices);
		m_vao.SetEB(m_ebo.GetID());
		m_vao.SetVB(m_vbo.GetID());
		m_vao.SetCount(m_ebo.GetCount());
		m_vao.PushAttrib<float>(3);
		m_vao.PushAttrib<float>(3);
		m_vao.PushAttrib<float>(2);
		m_vao.ApplyLayout();
		m_vao.SetMetaType(GL_TRIANGLES);
	}
	CubeSprite::CubeSprite(bool init)
		:QuadSprite(false)
	{
		if (init)
			Init();
	}

	void CubeSprite::Render(const glm::mat4& modelTrans)
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera == nullptr)
			return;
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::Mesh_V_N_T);
		if (shader == nullptr)
			return;

		LM::Texture* tex = m_Textures[0].m_Texture;
		tex->Bind();
		shader->Bind();
		shader->SetUniformTexture("u_Tex", tex->GetIndex());
		shader->SetUniform2f("u_TexOffset", m_Textures[0].offsetx, m_Textures[0].offsety);
		shader->SetUniform2f("u_TexScale", m_Textures[0].scalex, m_Textures[0].scaley);

		glm::mat4& mvpTrans = Renderer::GetMVPTrans();
		glm::mat3& normalTrans = Renderer::GetNormalTrans();
		glm::mat4& mvTrans = Renderer::GetMVTrans();
		mvTrans = camera->GetViewTrans() * modelTrans;
		mvpTrans = camera->GetProjectionTrans() * mvTrans;
		normalTrans = glm::transpose(glm::inverse(glm::mat3(modelTrans)));
		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));
		shader->SetUniformMatrix3f("u_NormalTrans", false, glm::value_ptr(normalTrans));
		shader->SetUniformMatrix4f("u_VTrans", false, glm::value_ptr(camera->GetViewTrans()));
		shader->SetUniform4f("u_Color", &m_Color[0].r);

		m_vao.DrawElement();
	}
}