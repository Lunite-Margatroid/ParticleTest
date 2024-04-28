#pragma once
#include "Shader.h"
namespace ptt
{
	class tfbShader:public LM::Shader
	{
	protected:
		unsigned int m_tfbID;
		std::vector<char*> m_Varyings;


		bool m_Active;
		bool m_Pause;

		void TransformFeedbackInit();
	public:
		tfbShader(const std::string& vertexShader, const std::string& fragmentShader);
		tfbShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
		virtual ~tfbShader();

		void BindTransformFeedback();
		void UnbindTransformFeedback();

		unsigned int GetTransformFeedbackID() const;

		virtual void BindBuffer(unsigned int index, unsigned int buffer);
		virtual void BindBufferRange(unsigned int index, unsigned int buffer, int offset, int size);

		virtual void ApplyVarying(GLenum bufferMode = GL_INTERLEAVED_ATTRIBS);

		void PushVarying(const char* varying);

		// Once Begin GL_TRANSFORM_FEEDBACK Can't Be Bind Until the TranformFeedback Object End.
		// Bind before begin.
		void BeginTransformFeedback(GLenum primitiveMode);
		void EndTransformFeedback();

		void PauseTransformFeedback();
		void ResumeTransformFeedback();
	};
}