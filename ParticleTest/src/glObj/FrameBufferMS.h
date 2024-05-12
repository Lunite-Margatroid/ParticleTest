#pragma once
#include "FrameBuffer.h"
namespace LM
{
	/// <summary>
	/// �ⶫ������ɫ���岻��ֱ����������
	/// ��Ϊ��������( -'`-)
	/// ���֡������Multi-Sampled Frame Buffer
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
		/// <param name="width"> ֡������</param>
		/// <param name="height"> ֡����߶�</param>
		/// <param name="nSample"> ���ز�������������</param>
		/// <param name="index"> Ĭ��ֵ�ͺ�</param>
		FrameBufferMS(int width, int height, unsigned char nSample = 4,unsigned char index = 0);
		/// <summary>
		/// ��n����ɫ����ϳ�һ�� ���͸�Ŀ��֡�������ɫ����
		/// </summary>
		/// <param name="framebuffer"></param>
		void BlitFrameBuffer(const FrameBuffer& framebuffer);
		/// <summary>
		/// ��n����ɫ����ϳ�һ�� ���͸�Ĭ��֡�������ɫ����
		/// </summary>
		void BlitFrameBuffer(int defaultBufferWidth, int defaultBufferHeight);

		virtual void Init(int width, int height, unsigned char nSample = 4, unsigned char index = 0);
	};
}