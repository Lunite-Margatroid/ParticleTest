#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"

namespace ptt
{
	class oitContext
	{
	private:
		GLuint m_HeadMat;
		GLuint m_HeadInitializer;
		GLuint m_AtomicCounter;
		GLuint m_ListBuffer;
		GLuint m_ListTex;
		
		int m_Width;
		int m_Height;

		LM::VertexArray m_vao;
		LM::VertexBuffer m_vbo;

		void InitDrawBuffer();
	public:
		oitContext();
		~oitContext();

		void RenderPreproc();
		void Render();
	};
}