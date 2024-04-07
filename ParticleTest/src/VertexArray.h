#pragma once
namespace LM {
	struct AttribLayout
	{
		unsigned int count;
		unsigned int type;
		bool bNormalize;
		
		AttribLayout(unsigned int c, unsigned int t, bool b)
			:count(c), type(t),bNormalize(b)
		{}

		static unsigned int GetSizeOfElem(unsigned int typ)
		{
			switch (typ)
			{
			case GL_FLOAT:return 4;
			case GL_UNSIGNED_INT:return 4;
			case GL_UNSIGNED_BYTE:return 1;
			}
			ASSERT(false);
			return 0;
		}
	};



	class VertexArray
	{
	private:
		unsigned int m_id;
		unsigned int m_stride;
		unsigned int m_vb;
		unsigned int m_eb;
		std::vector<AttribLayout> m_attribLayout;
		GLenum m_MetaType;
	public:
		VertexArray(GLenum type = GL_TRIANGLES);
		VertexArray(unsigned int vbo, unsigned int ebo, GLenum type = GL_TRIANGLES);
		virtual ~VertexArray();

		//void AddBuffer();

		// ���뵱ǰ���Ե�ά��
		template<class T>
		void PushAttrib(int count) {ASSERT(false)};

		// ���뵱ǰ���Ե�ά��
		template<>
		void PushAttrib<float>(int count)
		{
			m_attribLayout.push_back(AttribLayout(count, GL_FLOAT, GL_FALSE));
			m_stride += count * 4;
		}

		// ���뵱ǰ���Ե�ά��
		template<>
		void PushAttrib<unsigned int>(int count)
		{
			m_attribLayout.push_back(AttribLayout(count, GL_UNSIGNED_INT, GL_FALSE ));
			m_stride += count * 4;
		}

		// ���뵱ǰ���Ե�ά��
		template<>
		void PushAttrib<unsigned char>(int count)
		{
			m_attribLayout.push_back(AttribLayout(count, GL_UNSIGNED_BYTE, GL_TRUE ));
			m_stride += count;
		}
	
		void ApplyLayout();

		unsigned int GetID() const;

		GLenum GetMetaType() const;

		void SetMetaType(GLenum);

		void Bind() const;
		void Unbind() const;

		void DrawElement(unsigned int count, unsigned int offset = 0) const;
		void DrawElement(unsigned int count, unsigned int offset = 0);
		void DrawArray(unsigned int count, unsigned int offset = 0) const;
		void DrawArray(unsigned int count, unsigned int offset = 0);

		void SetVB(unsigned int  vb);
		void SetEB(unsigned int  eb);
	};
}