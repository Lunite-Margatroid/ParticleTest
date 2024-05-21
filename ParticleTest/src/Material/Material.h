#pragma once
#include "glObj/Texture.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"

namespace ptt
{
	class Material
	{
	public:
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

		Texture& GetTexture(LM::TextureType);

		void Init();
	public:
		Material();
		virtual ~Material();

		void SetTexture(LM::TextureType, const std::string& texName);
		void SetTexture(LM::TextureType, LM::Texture*);
		void SetTextureScale(LM::TextureType, float x, float y);
		void SetTextureOffset(LM::TextureType, float x, float y);

		const Texture& GetTexture(LM::TextureType) const;

		virtual void MaterialEditor();
		virtual void BindTexture();
		virtual void SetUniformMaterial(LM::Shader* shader);
	};
}