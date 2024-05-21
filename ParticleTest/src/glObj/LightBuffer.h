#pragma once
#include "Light/Light.h"
namespace ptt
{
	class LightBuffer
	{
	protected:
		int m_Count;
		unsigned int m_Buffer;
		LM::LightType m_LightType;
		unsigned int m_MaxSize;

	public:
		LightBuffer(int count, LM::Light* lights, LM::LightType lightType);
		LightBuffer();
		~LightBuffer();

		void Init(int count, LM::Light* lights);

		void BindToShaderStorage(LM::Shader* shader, const std::string& bufferName);
	};
}