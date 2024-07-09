#include "pch.h"
#include "AnimatedObj.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"

namespace ptt
{
	AnimatedObj::AnimatedObj(SceneObj* parent, Sprite* sprite, const std::string& objName)
		:SceneObj(parent, sprite, objName), m_bAnimated(false)
	{
	}
	void AnimatedObj::Update(float deltaTime)
	{
		for (SceneObj* child : m_ChildObj)
		{
			child->Update(deltaTime);
		}
		if (m_bAnimated)
		{
			m_FrameNode.Update(deltaTime);
			m_Position = m_FrameNode.GetPosFrame();
			m_Scale = m_FrameNode.GetScaleFrame();
			m_Qua = m_FrameNode.GetRotationFrame();
		}
		else
		{
			UpdateQuaternion();
		}

		if (m_Sprite)
			m_Sprite->Update(deltaTime);
	}
	void AnimatedObj::ReadAnimationScript(const std::string& path)
	{
		m_FrameNode.ReadScript(path);
	}
	void AnimatedObj::RenderImGui()
	{
		ImGui::SeparatorText("Object");
		ImGui::DragFloat3("Position", &m_Position.x, 0.1f);
		ImGui::Text("Rotate");
		ImGui::DragFloat("Pitch - xAxis", &m_Pitch,
			0.01f, -PI, PI, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat("Yaw - yAxis", &m_Yaw, 0.01f, -PI, PI, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat("Roll - zAxis", &m_Roll, 0.01f, -PI, PI, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat3("Scale", &m_Scale.x, 0.01f, -100.0f, 100.0f, "%.3f",
			ImGuiSliderFlags_AlwaysClamp);

		float* staggeringTransPtr = glm::value_ptr(m_StaggerTrans);
		ImGui::Separator();
		if (ImGui::Button("Reset Staggering"))
		{
			ResetStaggering();
		}
		ImGui::DragFloat3("##col1", staggeringTransPtr, 0.01f, -10.f, 10.f);
		ImGui::DragFloat3("##col2", staggeringTransPtr + 4, 0.01f, -10.f, 10.f);
		ImGui::DragFloat3("##col3", staggeringTransPtr + 8, 0.01f, -10.f, 10.f);

		ImGui::Separator();
		ImGui::Checkbox("Aniamted", &m_bAnimated);
		if (ImGui::Button("Reload Animation Script"))
		{
			IGFD::FileDialogConfig config;
			config.path = "./res/script";
			ImGuiFileDialog::Instance()->OpenDialog("Load Animation Script", "Choose File", ".txt", config);
		}
		if (ImGui::Button("Clear Animation"))
		{
			m_FrameNode.Clear();
		}
		// ---------------- Load Animation Script -------------------
		if (ImGuiFileDialog::Instance()->Display("Load Animation Script")) {
			if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				// action
				ReadAnimationScript(filePathName);
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}

		if (m_Sprite)
		{
			ImGui::SeparatorText("Sprite Property");
			if (ImGui::Button("Status Unite"))
			{
				StatusUnite();
			}
			m_Sprite->RenderImGui();
		}
	}
	void AnimatedObj::EnableAnimation(bool enableAnimation)
	{
		m_bAnimated = enableAnimation;
	}
	bool AnimatedObj::IsAnimated() const
	{
		return m_bAnimated;
	}
}
