#pragma once
#include "glObj/Texture.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	class Material
	{
	protected:
		struct Texture
		{
			LM::Texture* m_Texture;
			float offsetx, offsety;
			float scalex, scaley;
			float weight;
			Texture(LM::Texture* tex) :
				m_Texture(tex), offsetx(0.0f), offsety(0.0f), scalex(1.0f), scaley(1.f),weight(1.0f)
			{}
		};
	protected:
		Texture m_texDiffuse;
		Texture m_texSpecular;
		Texture m_texNormal;
		Texture m_texParallax;

		float m_Shininess;

		void Init();
	public:
		Material();
		virtual ~Material();

		void SetTexture(LM::TextureType, const std::string& texName);

		virtual void MaterialEditor();
	};
}