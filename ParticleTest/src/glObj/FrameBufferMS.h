#pragma once
#include "FrameBuffer.h"
namespace LM
{
	/// <summary>
	/// 这东西的颜色缓冲不能直接拿来绘制
	/// 因为。。。。( -'`-)
	/// 这个帧缓冲是Multi-Sampled Frame Buffer
	/// </summary>
	class FrameBufferMS: public FrameBuffer
	{
	protected:
		unsigned char m_nSample;
	public:
		FrameBufferMS() = default;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="width"> 帧缓冲宽度</param>
		/// <param name="height"> 帧缓冲高度</param>
		/// <param name="nSample"> 多重采样的样本层数</param>
		/// <param name="index"> 默认值就好</param>
		FrameBufferMS(int width, int height, unsigned char nSample = 4,unsigned char index = 0);
		/// <summary>
		/// 把n重颜色缓冲合成一个 发送给目标帧缓冲的颜色缓冲
		/// </summary>
		/// <param name="framebuffer"></param>
		void BlitFrameBuffer(const FrameBuffer& framebuffer);
		/// <summary>
		/// 把n重颜色缓冲合成一个 发送给默认帧缓冲的颜色缓冲
		/// </summary>
		void BlitFrameBuffer(int defaultBufferWidth, int defaultBufferHeight);

		virtual void Init(int width, int height, unsigned char nSample = 4, unsigned char index = 0);
	};
}