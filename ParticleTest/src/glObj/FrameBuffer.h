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

		float m_AspectRatio; // 宽高比

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
		/// 绑定纹理并返回纹理单元
		/// </summary>
		/// <returns></returns>
		unsigned char GetTexIndex() const;
		int GetWidth()const;
		int GetHeight()const;
		float GetAspectRatio() const;
	};
}