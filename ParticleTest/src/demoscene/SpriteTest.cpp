#include "pch.h"
#include "SpriteTest.h"

namespace ptt
{
	SpriteTest::SpriteTest():
		m_Color(1.0f, 1.0f, 1.f,1.f)
	{
		m_RootObj = std::make_unique<SceneObj>();
		m_SelectedObj = new SceneObj(nullptr, new QuadMeshSprite());
		m_RootObj->PushChild(m_SelectedObj);
		m_Shader = std::make_unique<LM::Shader>("./res/shader/QuadMeshSpriteVertex.shader", "./res/shader/QuadMeshSpriteFrag.shader");
		m_Camera = std::make_unique<Camera3D>();

		m_Yaw = m_SelectedObj->GetYaw();
		m_Pitch = m_SelectedObj->GetPitch();
		m_Roll = m_SelectedObj->GetRoll();

		m_Position = m_SelectedObj->GetPosition();

	}
	SpriteTest::~SpriteTest()
	{
	}
	void SpriteTest::Render()
	{
		Renderer::SetCurrentShader(m_Shader.get());
		Renderer::SetCurrentCamera(m_Camera.get());
		m_RootObj->Render();
	}
	void SpriteTest::RenderImGui()
	{
		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera)
		{
			const glm::vec3& cameraPos = camera->GetPosition();
			const glm::vec3& cameraAhead = camera->GetAhead();
			ImGui::Text("CameraPos: %.2f  %.2f  %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
			ImGui::Text("CameraAhead: %.2f  %.2f  %.2f", cameraAhead.x, cameraAhead.y, cameraAhead.z);
		}
		ImGui::SliderFloat3("Mesh Pos", &m_Position.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("Euler Angle", &m_Yaw, -PI, PI);
		ImGui::ColorEdit4("MeshColor", &m_Color.r);
	}
	void SpriteTest::Update(float deltaTime)
	{
		m_Camera->Update(deltaTime);
		m_RootObj->Update(deltaTime);

		m_SelectedObj->SetEulerAngle(&m_Yaw);
		m_SelectedObj->SetPosition(m_Position);

		QuadMeshSprite* sprite = dynamic_cast<QuadMeshSprite*>(m_SelectedObj->GetSprite());
		if (sprite)
		{
			sprite->SetMeshColor(m_Color);
		}
	}
	void QuadMeshSprite::Init()
	{
		const float tt = 1000.0f;
		float vertice[] =
		{
			// x      z
			-tt, -tt,
			-tt, tt,
			tt, tt,
			tt, -tt
		};

		m_Buffer.Init(sizeof(vertice), vertice, GL_STATIC_DRAW);
		m_VAO.SetVB(m_Buffer.GetID());
		m_VAO.PushAttrib<float>(2);
		m_VAO.ApplyLayout();
		m_VAO.SetMetaType(GL_TRIANGLE_FAN);
	}
	QuadMeshSprite::QuadMeshSprite():
		m_MeshColor(1.0f, 1.0f ,1.0f, 1.0f)
	{
		Init();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	QuadMeshSprite::~QuadMeshSprite()
	{
		glDisable(GL_BLEND);
	}
	void QuadMeshSprite::SetMeshColor(const glm::vec4& color)
	{
		m_MeshColor = color;
	}
	void QuadMeshSprite::Render(glm::mat4& modelTrans)
	{
		LM::Shader* shader = Renderer::GetCurrentShader();
		ASSERT(shader!=nullptr);
		Camera* camera = Renderer::GetCurrentCamera();
		ASSERT(camera != nullptr);
		static glm::mat4 mvpTrans(1.0f);
		static glm::mat4 mvTrans;
		mvTrans = camera->GetViewTrans() *
			modelTrans;
		mvpTrans =
			camera->GetProjectionTrans() * mvTrans;

		shader->SetUniformMatrix4f("u_MVPTrans", false, glm::value_ptr(mvpTrans));
		shader->SetUniform4f("u_MeshColor", m_MeshColor.r, m_MeshColor.g, m_MeshColor.b, m_MeshColor.a);
		shader->SetUniformMatrix4f("u_MVTrans", false, glm::value_ptr(mvTrans));

		m_VAO.DrawArray(4, 0);
		
	}
}