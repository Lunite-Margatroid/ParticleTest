#pragma once
namespace ptt
{
	class FrameNode
	{
	public:
		struct Node
		{
			float Time;
			float x, y, z;
			float s_x, s_y, s_z;
			float r_x, r_y, r_z;
		};
	protected:
		int m_Count;
		Node* m_Nodes;

		int m_CurCount;

		float m_MaxTime;
		float m_CurTime;

		glm::vec3 m_CurPos;
		glm::vec3 m_CurScale;
		glm::qua<float> m_CurRotation;
		
		void Init();
	public:
		FrameNode();
		FrameNode(const std::string& path);
		~FrameNode();

		void ReadScript(const std::string& path);
		void Clear();

		void Reset();

		void Update(float deltaTime);
		Node& GetNode(int index);

		const glm::vec3& GetPosFrame();
		const glm::vec3& GetScaleFrame();
		const glm::qua<float>& GetRotationFrame();

		Node GetFrame(float Time);

		void Print();
	
	};

}