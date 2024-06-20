#pragma once
#include "Shader/Shader.h"
#include "Interface/ImGuiInterface.h"

namespace ptt
{
	class Sprite : public ImGuiInterface
	{
	protected:
		LM::Shader* m_Shader;
		LM::Shaders m_ShaderName;
		bool m_Transparency;
		bool m_Visible;
		bool m_Lighted;
	public:
		Sprite();
		virtual ~Sprite();
		virtual void Render(const glm::mat4& modelTrans);

		bool IsTransparency() const;
		bool IsVisible()const;
		bool SetVisible(bool visible);
		void SetTransparency(bool transparency);
		bool IsLighted() const;
		void SetLighted(bool lighted);

		void ShaderSelector();

		virtual void RenderImGui() override;
		virtual void SelectShader();

		virtual void Update(float deltaTime);

		LM::Shaders GetShaderName() const;
		void SetShaderName(LM::Shaders);
	};
}