#pragma once
namespace LM {
	struct AttribLayout
	{
		unsigned int count;		// dimesion of the attrib
		unsigned int type;		// data type of the attrib
		bool bNormalize;		// if normal
		bool skip;

		static const bool skip_arrtib;
		
		AttribLayout(unsigned int c, unsigned int t, bool b,bool s = false)
			:count(c), type(t),bNormalize(b),skip(s)
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

		// 输入当前属性的维度
		template<class T>
		void PushAttrib(int count, bool skip = false) {ASSERT(false)};

		// 输入当前属性的维度
		template<>
		void PushAttrib<float>(int count, bool skip)
		{
			m_attribLayout.push_back(AttribLayout(count, GL_FLOAT, GL_FALSE,skip));
			m_stride += count * 4;
		}

		// 输入当前属性的维度
		template<>
		void PushAttrib<unsigned int>(int count, bool skip)
		{
			m_attribLayout.push_back(AttribLayout(count, GL_UNSIGNED_INT, GL_FALSE ,skip));
			m_stride += count * 4;
		}

		// 输入当前属性的维度
		template<>
		void PushAttrib<unsigned char>(int count, bool skip)
		{
			m_attribLayout.push_back(AttribLayout(count, GL_UNSIGNED_BYTE, GL_TRUE ,skip));
			m_stride += count;
		}
	
		void ApplyLayout(unsigned int bufferOffset = 0u);
		void ApplyLayoutSeparate(int numOfVertice);

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