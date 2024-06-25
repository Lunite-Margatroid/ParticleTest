#include "pch.h"
#include "FrameNode.h"

namespace ptt
{
	void FrameNode::Init()
	{
		m_Count = 0;
		m_Nodes = nullptr;
		m_CurCount = -1;
		m_MaxTime = 0.f;
		m_CurTime = 0.f;

		m_CurPos = glm::vec3(0.0f);
		m_CurScale = glm::vec3(1.0f, 1.f, 1.f);
		m_CurRotation = glm::qua<float>(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	FrameNode::FrameNode()
	{
		Init();
	}
	FrameNode::FrameNode(const std::string& path)
	{
		Init();
		ReadScript(path);
	}
	FrameNode::~FrameNode()
	{
		Clear();
	}
	void FrameNode::ReadScript(const std::string& path)
	{
		std::fstream file;
		file.open(path, std::ios::in);
		if (file)
		{
			file >> m_Count;
			m_Nodes = new Node[m_Count];
			for (int i = 0; i < m_Count; i++)
			{
				if (file.eof())
				{
					std::cout << "Script Error." << std::endl;
				}
				file >> m_Nodes[i].Time;
				file >> m_Nodes[i].x >> m_Nodes[i].y >> m_Nodes[i].z;
				file >> m_Nodes[i].s_x >> m_Nodes[i].s_y >> m_Nodes[i].s_z;
				file >> m_Nodes[i].r_x >> m_Nodes[i].r_y >> m_Nodes[i].r_z;
			}
			file.close();
			m_MaxTime = m_Nodes[m_Count - 1].Time;
		}
		else
		{
			std::cout << "Can't open file: " << path << std::endl;
		}
		Print();
	}
	void FrameNode::Clear()
	{
		if (m_Nodes)
			delete[] m_Nodes;
		Init();
	}
	void FrameNode::Reset()
	{
		m_CurCount = 0;
		m_CurTime = 0.0f;
		m_CurPos = glm::vec3(0.0f);
		m_CurScale = glm::vec3(1.0f);
		m_CurRotation = glm::qua<float>(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	void FrameNode::Update(float deltaTime)
	{
		if (m_Count == 0)
		{
			Reset();
			return;
		}
		m_CurTime += deltaTime;
		if (m_CurTime > m_MaxTime)
		{
			m_CurTime = 0.0f;
			m_CurCount = 0;
		}
		while (m_CurTime >= m_Nodes[m_CurCount].Time)
		{
			m_CurCount++;
		}
		Node& n1 = GetNode(m_CurCount - 1);
		Node& n2 = GetNode(m_CurCount);
		if (n1.Time == n2.Time)
		{
			m_CurPos = glm::vec3(n1.x, n1.y, n1.z);
			m_CurScale = glm::vec3(n1.s_x, n1.s_y, n1.s_z);
			m_CurRotation = glm::qua<float>(glm::vec3(n1.r_x, n1.r_y, n1.r_z));
			return;
		}
		float t = (m_CurTime - n1.Time) / (n2.Time - n1.Time);
		t = t > 0.0f ? (t <= 1.0f ? t : 1.0f) : 0.0f;
		m_CurPos = glm::mix(glm::vec3(n1.x, n1.y, n1.z), glm::vec3(n2.x, n2.y, n2.z), t);
		m_CurScale = glm::mix(glm::vec3(n1.s_x, n1.s_y, n1.s_z), glm::vec3(n2.s_x, n2.s_y, n2.s_z), t);
		m_CurRotation = glm::slerp(
			glm::qua<float>(glm::vec3(n1.r_x, n1.r_y, n1.r_z)),
			glm::qua<float>(glm::vec3(n2.r_x, n2.r_y, n2.r_z)),
			t);
	}
	FrameNode::Node& FrameNode::GetNode(int index)
	{
		// TODO: insert return statement here
		index = index >= 0 ? index : 0;
		index = index < m_Count ? index : m_Count - 1;
		return m_Nodes[index];
	}
	const glm::vec3& FrameNode::GetPosFrame()
	{
		// TODO: insert return statement here
		return m_CurPos;
	}
	const glm::vec3& FrameNode::GetScaleFrame()
	{
		// TODO: insert return statement here
		return m_CurScale;
	}
	const glm::qua<float>& FrameNode::GetRotationFrame()
	{
		// TODO: insert return statement here
		return m_CurRotation;
	}
	void FrameNode::Print()
	{
		std::cout << "Frame Count:" << m_Count << std::endl;
		for (int i = 0; i < m_Count; i++)
		{
			std::cout << "Frame " << i + 1 << ": ";
			std::cout << "Time " << m_Nodes[i].Time << "s\n";
			std::cout << "x: " << m_Nodes[i].x << " y: " << m_Nodes[i].y << " z: " << m_Nodes[i].z << std::endl;
			std::cout << "scale_x: " << m_Nodes[i].s_x << " scale_y: " << m_Nodes[i].s_y << " scale_z: " << m_Nodes[i].s_z << std::endl;
			std::cout << "rotation_x: " << m_Nodes[i].r_x << " rotation_y: " << m_Nodes[i].r_y << " rotation_z: " << m_Nodes[i].r_z << std::endl << std::endl;
		}
	}
}