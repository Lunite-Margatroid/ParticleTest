#pragma once
#include "DemoScene.h"
#include "SceneObj/SceneObj.h"
#include "Sprite/Sprite.h"
#include "Shader.h"
#include "Camera3D.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
namespace ptt
{
	class QuadMeshSprite :public Sprite
	{
	private:
		LM::VertexBuffer m_Buffer;
		LM::VertexArray m_VAO;

		glm::vec4 m_MeshColor;

		void Init();
	public:
		QuadMeshSprite();
		~QuadMeshSprite();

		virtual void Render(glm::mat4& modelTrans) override;
	};

	class SpriteTest:public DemoScene
	{
	protected:
		std::unique_ptr<SceneObj> m_RootObj;
		std::unique_ptr<LM::Shader> m_Shader;
		std::unique_ptr<Camera3D> m_Camera;
		SceneObj* m_SelectedObj;
	public:
		SpriteTest();
		virtual ~SpriteTest();

		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}