#pragma once
#include "Sprite.h"
namespace ptt
{
	template <int n>
	class ColoredSprite :public Sprite
	{
	protected:
		glm::vec4 m_Color[n];

	public:
		ColoredSprite()
		{
			for (int i = 0; i < n; i++)
			{
				m_Color[i] = glm::vec4(1.0f);
			}
		}
		virtual ~ColoredSprite()
		{
		}

		const glm::vec4& GetColor(int index) const
		{
			ASSERT(index >= 0 && index < n);
			return m_Color[index];
		}
		void SetColor(const glm::vec4& color, int index)
		{
			ASSERT(index >= 0 && index < n);
			m_Color[index] = color;
		}

		int GetColorCount()
		{
			return n;
		}
	};

}