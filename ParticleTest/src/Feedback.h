#pragma once
namespace ptt
{
	// transform feedback
	class Feedback
	{
	protected:
		unsigned int m_tfID;
		std::vector<char*> m_Varyings;


		virtual void Init();
	public:
		Feedback();
		~Feedback();

		void Bind();

		unsigned int GetTransformFeedbackID() const;
	
		virtual void BindBuffer(unsigned int index, unsigned int buffer);

		virtual void ApplyVarying(GLenum bufferMode = GL_INTERLEAVED_ATTRIBS);

		void PushVarying();
	};
}