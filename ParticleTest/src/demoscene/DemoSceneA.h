#pragma once
#include "DemoScene.h"
#include "SceneObj/SceneObj.h"
#include "Sprite/QuadMeshSprite.h"
#include "Sprite/Hanabi.h"
#include "Sprite/QuadSprite.h"
#include "Sprite/CubeSprite.h"
namespace ptt
{
	class DemoSceneA :public DemoScene
	{
	protected:
		std::unique_ptr<SceneObj> m_RootObj;
		Camera* m_Camera;
		SceneObj* m_SelectedObj;

		virtual void Init();
		void DrawObjTree(const SceneObj&);
		
	public:
		DemoSceneA(bool init);			// 供子类使用的构造函数
		DemoSceneA();
		virtual ~DemoSceneA();

		void Render() override;
		void RenderImGui() override;
		void Update(float deltaTime) override;
	};
}