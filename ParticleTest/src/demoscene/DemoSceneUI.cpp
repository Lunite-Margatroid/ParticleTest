#include "pch.h"
#include "DemoSceneUI.h"

namespace ptt
{
	void DemoSceneUI::Init()
	{
		LightedDemoScene::Init();

		InitUI();
	}
	void DemoSceneUI::InitUI()
	{
		const int segment = 12;
		const float radio_1 = 0.025f;
		const float radio_2 = 0.06f;
		const size_t vertexCount = (segment + 1) * 3 + 1;
		const size_t vertexBufferSize = vertexCount * 3 * sizeof(float);
		float* vertice = new float[vertexCount * 3];
		size_t p = 0;
		vertice[0] = 1.0f;
		vertice[1] = 0.0f;
		vertice[2] = 0.0f;
		p += 3;
		for (int i = 0; i <= segment; i++)
		{
			float* temp = vertice + p;
			p += 3;
			float theta = 2 * PI * i / segment;
			float cos_t = cosf(theta);
			float sin_t = sinf(theta);
			temp[0] = 0.9f;
			temp[1] = cos_t * radio_2;
			temp[2] = sin_t * radio_2;

			temp[3 * (segment + 1) ] = 0.95f;
			temp[3 * (segment + 1) + 1] = cos_t * radio_1;
			temp[3 * (segment + 1) + 2] = sin_t * radio_1;

			temp[3 * (segment + 1) * 2] = 0.0f;
			temp[3 * (segment + 1) * 2 + 1] = temp[3 * (segment + 1) + 1];
			temp[3 * (segment + 1) * 2 + 2] = temp[3 * (segment + 1) + 2];
		}

		for (int i = 0; i < vertexCount; i++)
		{
			std::cout << i <<": ("<< vertice[i * 3] << ',' << vertice[i * 3 + 1] << ',' << vertice[i * 3 + 2] << ")\n";
		}

		const size_t elementCount = (segment + 1) * 4;
		const size_t elementSize = elementCount * sizeof(unsigned int);

		unsigned int* element = new unsigned int[elementCount];
		p = 0;
		for (int i = 0; i <= segment; i++)
		{
			element[i * 2] = i + 1;
			element[i * 2 + 1] = 0;
			element[i * 2 + (segment + 1) * 2] = (1 + segment) + 1 + i;
			element[i * 2 + 1 + (segment + 1) * 2] = (1 + segment) * 2 + 1 + i;
		}
		for (int i = 0; i < elementCount; i++)
		{
			std::cout << element[i] << "\t";
		}
		m_uiBuffer.Init(vertexBufferSize, vertice);
		m_uiEleBuffer.Init(elementCount, element);
		m_uiVertexArray.SetMetaType(GL_TRIANGLE_STRIP);
		m_uiVertexArray.SetEB(m_uiEleBuffer.GetID());
		m_uiVertexArray.SetVB(m_uiBuffer.GetID());

		m_uiVertexArray.SetCount(elementCount);
		m_uiVertexArray.PushAttrib<float>(3);
		m_uiVertexArray.ApplyLayout();

		delete[] vertice;
		delete[] element;
	}
	DemoSceneUI::DemoSceneUI()
		:LightedDemoScene(false)
	{
		Init();
	}
	DemoSceneUI::~DemoSceneUI()
	{
	}
	void DemoSceneUI::RenderUI()
	{
		LM::Shader* shader = Renderer::GetShader(Renderer::Shaders::UI_ObjAxis);
		if (shader == nullptr)
			return;
		Camera* camera = Renderer::GetCurrentCamera();
		if (camera == nullptr)
			return;
		shader->Bind();

		glm::mat4 mvpTrans;
		glm::mat4 modalTrans = glm::mat4(1.0f);
		modalTrans = glm::translate(modalTrans, m_SelectedObj->GetPosition());
		SceneObj::QuaternionRotate(modalTrans, m_SelectedObj->GetQuaternionRotate());
		mvpTrans = camera->GetProjectionTrans() *  camera->GetViewTrans() * modalTrans;
		//mvpTrans = camera->GetProjectionTrans();

		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));

		m_uiVertexArray.DrawElementInstanced(3);
		// m_uiVertexArray.DrawArrayInstanced(3);
	}
	void DemoSceneUI::Render()
	{
		LightedDemoScene::Render();
		GLboolean depthTest = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		RenderUI();
		if (depthTest)
			glEnable(GL_DEPTH_TEST);
	}
}
