#pragma once
#include "ImGuiDialogModal.h"


namespace ptt
{
	class RenderSetting : public ImGuiDialogModal
	{
	protected:
		GLenum m_BlendFactors[14];
		float m_Constant[4];

		GLenum m_SrcFactor_RGB;
		GLenum m_DstFactor_RGB;
		GLenum m_SrcFactor_Alpha;
		GLenum m_DstFactor_Alpha;

		GLenum m_BlendEquation_RGB;
		GLenum m_BlendEquation_Alpha;
		GLenum m_BlendEquationModes[5];

		GLboolean m_IfBlend;

		GLboolean m_IfCullFace;
		GLenum m_CullFace;
		GLenum m_CullFaceModes[5];

		GLboolean m_IfDepthTest;

		std::map<GLenum, std::string> m_NameMap;


		Camera3D::Projection m_Projection;

		GLenum m_PolygonModes[3];
		GLenum m_PolygonMode;

		float m_LineWidth;

		void Init();
	public:
		RenderSetting(const std::string& name);

		void ShowWindow() override;
		void InitWindow();
		void Apply();
		void SetDefault();

		void Popup() override;
	};
}