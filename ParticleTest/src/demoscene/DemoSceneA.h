#pragma once
#include "DemoScene.h"
#include "SceneObj/SceneObj.h"
#include "Sprite/QuadMeshSprite.h"
#include "Sprite/Hanabi.h"
#include "Sprite/QuadSprite.h"
#include "Sprite/CubeSprite.h"
#include "SceneObj/PerspectiveCamera.h"
#include "SceneObj/OrthoCamera.h"

namespace ptt
{
	class DemoSceneA :public DemoScene
	{
	protected:
		std::unique_ptr<SceneObj> m_RootObj;
		CameraObj* m_MainCamera;
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

		void SetMainCamera(CameraObj* camera);
	};
}