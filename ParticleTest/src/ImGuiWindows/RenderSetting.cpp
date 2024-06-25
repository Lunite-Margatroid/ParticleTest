#include "pch.h"
#include "RenderSetting.h"
#include "Renderer/Renderer.h"

namespace ptt
{
	void RenderSetting::Init()
	{
		m_NameMap[m_BlendFactors[0] = GL_ZERO				] = std::string("Zero");
		m_NameMap[m_BlendFactors[1] = GL_ONE				] = std::string("One");
		m_NameMap[m_BlendFactors[2] = GL_SRC_COLOR			] = std::string("Src Color");
		m_NameMap[m_BlendFactors[3] = GL_ONE_MINUS_SRC_COLOR] = std::string("1 - Src Color");
		m_NameMap[m_BlendFactors[4] = GL_DST_COLOR			] = std::string("Dst Color");
		m_NameMap[m_BlendFactors[5] = GL_ONE_MINUS_DST_COLOR] = std::string("1 - Dst Color");
		m_NameMap[m_BlendFactors[6] = GL_SRC_ALPHA			] = std::string("a of Src");
		m_NameMap[m_BlendFactors[7] = GL_ONE_MINUS_SRC_ALPHA] = std::string("1 - a of Src");
		m_NameMap[m_BlendFactors[8] = GL_DST_ALPHA			] = std::string("a of Dst");
		m_NameMap[m_BlendFactors[9] = GL_ONE_MINUS_DST_ALPHA] = std::string("1 - a of Dst");
		m_NameMap[m_BlendFactors[10] = GL_CONSTANT_COLOR	] = std::string("Constant");
		m_NameMap[m_BlendFactors[11] = GL_ONE_MINUS_CONSTANT_COLOR] = std::string("1 - constant");
		m_NameMap[m_BlendFactors[12] = GL_CONSTANT_ALPHA		  ] = std::string("a of constant");
		m_NameMap[m_BlendFactors[13] = GL_ONE_MINUS_CONSTANT_ALPHA] = std::string("1 - a of constant");

		m_NameMap[m_CullFaceModes[0] = GL_FRONT]			= std::string("Front Face");
		m_NameMap[m_CullFaceModes[1] = GL_BACK]				= std::string("Back Face");
		m_NameMap[m_CullFaceModes[2] = GL_FRONT_AND_BACK]	= std::string("Both of Front and Back");

		m_NameMap[m_BlendEquationModes[0] = GL_FUNC_ADD]				= std::string("+");
		m_NameMap[m_BlendEquationModes[1] = GL_FUNC_SUBTRACT]			= std::string("-");
		m_NameMap[m_BlendEquationModes[2] = GL_FUNC_REVERSE_SUBTRACT]	= std::string("reverse -");
		m_NameMap[m_BlendEquationModes[3] = GL_MIN]						= std::string("min");
		m_NameMap[m_BlendEquationModes[4] = GL_MAX]						= std::string("max");

		m_NameMap[m_PolygonModes[0] = GL_POINT] = std::string("Point");
		m_NameMap[m_PolygonModes[1] = GL_LINE] = std::string("Line");
		m_NameMap[m_PolygonModes[2] = GL_FILL] = std::string("Fill");

		m_NameMap[Camera3D::Ortho + 8]		  = std::string("Orthographic Projection");
		m_NameMap[Camera3D::Perspective + 8] = std::string("Perspective Projection");

		m_IfCullFace = GL_FALSE;
		m_CullFace = GL_BACK;
		m_IfDepthTest = GL_TRUE;
		m_IfBlend = GL_TRUE;
		m_SrcFactor_RGB = m_SrcFactor_Alpha = GL_SRC_ALPHA;
		m_DstFactor_RGB = m_DstFactor_Alpha = GL_ONE_MINUS_SRC_ALPHA;
		m_BlendEquation_RGB = m_BlendEquation_Alpha = GL_FUNC_ADD;
		m_Projection = Camera3D::Perspective;
		m_PolygonMode = GL_FILL;
		m_LineWidth = 1.0f;
	}
	RenderSetting::RenderSetting(const std::string& name)
		:ImGuiDialogModal(name)
	{
		Init();
	}
	void RenderSetting::ShowWindow()
	{
		if (WindowBegin())
		{
			if (ImGui::Button("Default"))
			{
				SetDefault();
			}
			// ---------------- Depth test ----------------
			ImGui::SeparatorText("Depth Test");
			if (ImGui::Checkbox("Depth-Test", reinterpret_cast<bool*>(&m_IfDepthTest)));
		

			// ------------------ blend ------------------
			ImGui::SeparatorText("Blend");
			ImGui::Checkbox("Enable Blend", reinterpret_cast<bool*>(&m_IfBlend));

			ImGui::BeginChild("##Blend Src Factor RGB", ImVec2(0.f, 0.f),
				ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);
			if (ImGui::BeginCombo("Blend Src Factor RGB", m_NameMap[m_SrcFactor_RGB].c_str()))
			{
				for (int i = 0; i < 14; i++)
				{
					bool isSelected = m_SrcFactor_RGB == m_BlendFactors[i];
					if (ImGui::Selectable(m_NameMap[m_BlendFactors[i]].c_str(), &isSelected))
					{
						m_SrcFactor_RGB = m_BlendFactors[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::EndChild();

			ImGui::BeginChild("##Blend Src Factor Alpha", ImVec2(0.f, 0.f),
				ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);
			if (ImGui::BeginCombo("Blend Src Factor Alpha", m_NameMap[m_SrcFactor_Alpha].c_str()))
			{
				for (int i = 0; i < 14; i++)
				{
					bool isSelected = m_SrcFactor_Alpha == m_BlendFactors[i];
					if (ImGui::Selectable(m_NameMap[m_BlendFactors[i]].c_str(), &isSelected))
					{
						m_SrcFactor_Alpha = m_BlendFactors[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::EndChild();


			ImGui::BeginChild("##Blend Dst Factor RGB", ImVec2(0.f, 0.f),
				ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);
			if (ImGui::BeginCombo("Blend Dst Factor RGB", m_NameMap[m_DstFactor_RGB].c_str()))
			{
				for (int i = 0; i < 14; i++)
				{
					bool isSelected = m_DstFactor_RGB == m_BlendFactors[i];
					if (ImGui::Selectable(m_NameMap[m_BlendFactors[i]].c_str(), &isSelected))
					{
						m_DstFactor_RGB = m_BlendFactors[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::EndChild();

			ImGui::BeginChild("##Blend Dst Factor Alpha", ImVec2(0.f, 0.f),
				ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);
			if (ImGui::BeginCombo("Blend Dst Factor Alpha", m_NameMap[m_DstFactor_Alpha].c_str()))
			{
				for (int i = 0; i < 14; i++)
				{
					bool isSelected = m_DstFactor_Alpha == m_BlendFactors[i];
					if (ImGui::Selectable(m_NameMap[m_BlendFactors[i]].c_str(), &isSelected))
					{
						m_DstFactor_Alpha = m_BlendFactors[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::EndChild();


			ImGui::BeginChild("##Blend Equation Func RGB", ImVec2(0.f, 0.f),
				ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);
			if (ImGui::BeginCombo("Blend Equation Func RGB", m_NameMap[m_BlendEquation_RGB].c_str()))
			{
				for (int i = 0; i < 5;i++)
				{
					bool isSelected = m_BlendEquation_RGB == m_BlendEquationModes[i];
					if (ImGui::Selectable(m_NameMap[m_BlendEquationModes[i]].c_str()))
					{
						m_BlendEquation_RGB = m_BlendEquationModes[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::EndChild();

			ImGui::BeginChild("##Blend Equation Func Alpha", ImVec2(0.f, 0.f),
				ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);
			if (ImGui::BeginCombo("Blend Equation Func Alpha", m_NameMap[m_BlendEquation_Alpha].c_str()))
			{
				for (int i = 0; i < 5; i++)
				{
					bool isSelected = m_BlendEquation_Alpha == m_BlendEquationModes[i];
					if (ImGui::Selectable(m_NameMap[m_BlendEquationModes[i]].c_str()))
					{
						m_BlendEquation_Alpha = m_BlendEquationModes[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::EndChild();

			// ------------------------ Cull face --------------------
			ImGui::SeparatorText("Cull Face");
			ImGui::Checkbox("Cull-Face", reinterpret_cast<bool*>(&m_IfCullFace));
			if (ImGui::BeginCombo("Cull Face Mode", m_NameMap[m_CullFace].c_str()))
			{
				for (int i = 0; i < 3; i++)
				{
					bool isSelected = m_CullFace == m_CullFaceModes[i];
					if (ImGui::Selectable(m_NameMap[m_CullFaceModes[i]].c_str(), &isSelected))
					{
						m_CullFace = m_CullFaceModes[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			// -------------------- projection -----------------
			ImGui::Separator();
			if (ImGui::BeginCombo("Projection", m_NameMap[m_Projection + 8].c_str()))
			{
				bool isSelected = m_Projection == Camera3D::Perspective;
				if (ImGui::Selectable(m_NameMap[Camera3D::Perspective + 8].c_str(), &isSelected))
				{
					m_Projection = Camera3D::Perspective;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}

				isSelected = m_Projection == Camera3D::Ortho;
				if (ImGui::Selectable(m_NameMap[Camera3D::Ortho + 8].c_str(), &isSelected))
				{
					m_Projection = Camera3D::Ortho;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
			ImGui::Separator();
			if (ImGui::BeginCombo("Polygon Mode", m_NameMap[m_PolygonMode].c_str()))
			{
				for (int i = 0; i < 3; i++)
				{
					bool isSelected = m_PolygonMode == m_PolygonModes[i];
					if (ImGui::Selectable(m_NameMap[m_PolygonModes[i]].c_str(), &isSelected))
					{
						m_PolygonMode = m_PolygonModes[i];
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::DragFloat("Line Width", &m_LineWidth, 0.01, 0, 10.f);

			// ------------------------ apply ---------------

			if (ImGui::Button("Apply"))
			{
				Apply();
			}
			if (ImGui::Button("OK"))
			{
				Apply();
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			WindowEnd();
		}
	}
	void RenderSetting::InitWindow()
	{
		glGetBooleanv(GL_BLEND, &m_IfBlend);
		glGetFloatv(GL_BLEND_COLOR, m_Constant);
		glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&m_DstFactor_RGB);
		glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&m_SrcFactor_RGB);
		glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&m_DstFactor_Alpha);
		glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&m_SrcFactor_Alpha);

		glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&m_BlendEquation_RGB);
		glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&m_BlendEquation_Alpha);

		glGetBooleanv(GL_CULL_FACE, &m_IfCullFace);
		glGetIntegerv(GL_CULL_FACE_MODE, (GLint*)&m_CullFace);

		glGetBooleanv(GL_DEPTH_TEST, &m_IfDepthTest);

		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera)
		{
			m_Projection = camera->GetProjectionType();
		}

	}
	void RenderSetting::Apply()
	{
		// ---------- cull face -------------
		if (m_IfCullFace)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
		glCullFace(m_CullFace);
		// ----------Depth Test ----------------
		if (m_IfDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
		// ----------- blend ----------------
		if (m_IfBlend)
		{
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		glBlendFuncSeparate(m_SrcFactor_RGB, m_DstFactor_RGB, m_SrcFactor_Alpha, m_DstFactor_Alpha);
		glBlendEquationSeparate(m_BlendEquation_RGB, m_BlendEquation_Alpha);

		Camera3D* camera = dynamic_cast<Camera3D*>(Renderer::GetCurrentCamera());
		if (camera)
		{
			if (m_Projection == Camera3D::Perspective)
				camera->SetPerspectiveProjection();
			else if (m_Projection == Camera3D::Ortho)
				camera->SetOrthoProjection();
		}

		glLineWidth(m_LineWidth);
		glPolygonMode(GL_FRONT_AND_BACK, m_PolygonMode);
	}
	void RenderSetting::SetDefault()
	{
		m_IfCullFace = GL_FALSE;
		m_CullFace = GL_BACK;
		m_IfDepthTest = GL_TRUE;
		m_IfBlend = GL_TRUE;
		m_SrcFactor_RGB = m_SrcFactor_Alpha = GL_SRC_ALPHA;
		m_DstFactor_RGB = m_DstFactor_Alpha = GL_ONE_MINUS_SRC_ALPHA; 
		m_BlendEquation_RGB = m_BlendEquation_Alpha = GL_FUNC_ADD;
		m_Projection = Camera3D::Perspective;
		m_PolygonMode = GL_FILL;
		m_LineWidth = 1.f;
		Apply();
	}
	void RenderSetting::Popup()
	{
		ImGuiDialog::Popup();
		InitWindow();
	}
}