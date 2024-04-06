#pragma once
namespace ptt
{
	class DemoScene
	{
	protected:

	public:
		DemoScene();
		virtual ~DemoScene();

		virtual bool ShouleClose();
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void RenderImGui();
	
	};

	class MunuScene :public DemoScene
	{
	private:

	public:

	};
}