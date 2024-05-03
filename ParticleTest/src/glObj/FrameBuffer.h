#pragma once
namespace LM
{
	class FrameBuffer
	{
	protected:
		unsigned int m_fboID;		// frame buffer object id
		unsigned int m_texID;		// texture id
		unsigned int m_rboID;		// render buffer object id
		int m_width;
		int m_height;
		unsigned char m_texIndex;

		float m_AspectRatio; // ��߱�

	public:
		FrameBuffer();
		FrameBuffer(int width, int height, unsigned char index=0);
		virtual ~FrameBuffer();
		virtual void Init(int width, int height);
		void Bind();
		void Unbind();
		unsigned int GetFrameBufferID()const;
		unsigned int GetTextureID() const;
		/// <summary>
		/// ��������������Ԫ
		/// </summary>
		/// <returns></returns>
		unsigned char GetTexIndex() const;
		int GetWidth()const;
		int GetHeight()const;
		float GetAspectRatio() const;
	};
}