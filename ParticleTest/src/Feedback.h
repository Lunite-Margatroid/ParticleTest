#pragma once
namespace ptt
{
	// transform feedback
	class Feedback
	{
	protected:
		unsigned int m_tfID;
		std::vector<char*> m_Varyings;
		

		static bool s_Active;
		static bool s_Pause;

		virtual void Init();
	public:
		Feedback();
		~Feedback();

		void Bind();
		void Unbind();

		unsigned int GetTransformFeedbackID() const;
	
		virtual void BindBuffer(unsigned int index, unsigned int buffer);
		virtual void BindBufferRange(unsigned int index, unsigned int buffer, int offset, int size);

		virtual void ApplyVarying(unsigned int program , GLenum bufferMode = GL_INTERLEAVED_ATTRIBS);

		void PushVarying(const char* varying);

		// Once Begin GL_TRANSFORM_FEEDBACK Can't Be Bind Until the TranformFeedback Object End.
		// Bind before begin.
		static void BeginTransformFeedback(GLenum primitiveMode);
		static void EndTransformFeedback();

		static void PauseTransformFeedback();
		static void ResumeTransformFeedback();

	};
}