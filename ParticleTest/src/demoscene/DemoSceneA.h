#pragma once
#include "DemoScene.h"
#include "SceneObj/SceneObj.h"
#include "Sprite/QuadMeshSprite.h"
#include "Sprite/Hanabi.h"
namespace ptt
{
	class DemoSceneA :public DemoScene
	{
	protected:
		std::unique_ptr<SceneObj> m_RootObj;
		LM::Shader* m_Shader;
		Camera3D* m_Camera;
		SceneObj* m_SelectedObj;

		virtual void Init();
	public:
		DemoSceneA() = delete;	// forbid default structor
		DemoSceneA(bool init = true);
		virtual ~DemoSceneA();

		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}