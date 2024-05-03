#pragma once
#include "DemoScene.h"
#include "SceneObj/SceneObj.h"
#include "Shader/Shader.h"
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

		void DrawObjTree(const SceneObj&);
	public:
		SpriteTest();
		virtual ~SpriteTest();

		

		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;


	};
}