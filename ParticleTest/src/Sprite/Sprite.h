#pragma once
namespace ptt
{
	class Sprite
	{
	protected:

	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(glm::mat4& modelTrans);
	};
}