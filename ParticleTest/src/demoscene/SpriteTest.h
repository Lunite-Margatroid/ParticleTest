#pragma once
#include "DemoScene.h"
#include "SceneObj/SceneObj.h"
#include "Shader.h"
#include "Camera3D.h"
#include "Renderer/Renderer.h"
#include "Sprite/QuadMeshSprite.h"
namespace ptt
{
	class SpriteTest:public DemoScene
	{
	protected:
		std::unique_ptr<SceneObj> m_RootObj;
		std::unique_ptr<LM::Shader> m_Shader;
		std::unique_ptr<Camera3D> m_Camera;
		SceneObj* m_SelectedObj;

		glm::vec3 m_Position;
		float m_Yaw;
		float m_Pitch;
		float m_Roll;

		glm::vec4 m_Color;
	public:
		SpriteTest();
		virtual ~SpriteTest();

		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}