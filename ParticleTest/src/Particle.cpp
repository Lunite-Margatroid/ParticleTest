#include "pch.h"
#include "Particle.h"
namespace ptt
{
    Particle::Particle()
        :m_ParticleNum(300)
    {
        Init();
    }
    Particle::Particle(int nParticle)
        :m_ParticleNum(nParticle)
    {
        Init();
    }
    void Particle::EnableAngleLimite()
    {
        ASSERT(!m_AngleLimite);
        m_AngleLimite = true;
    }
    void Particle::DisableAngleLimite()
    {
        ASSERT(m_AngleLimite);
        m_AngleLimite = false;
    }
    void Particle::SetAngleRangeX(float low, float high)
    {
        ASSERT(low <= high);
        m_AngleRangeX[0] = low;
        m_AngleRangeX[1] = high;
    }
    void Particle::SetAngleRangeY(float low, float high)
    {
        ASSERT(low <= high);
        m_AngleRangeY[0] = low;
        m_AngleRangeY[1] = high;
    }
    void Particle::SetVelocityRange(float low, float high)
    {
        ASSERT(low <= high);
        m_VelocityRange[0] = low;
        m_VelocityRange[1] = high;
    }
    void Particle::SetTimeRange(float low, float high)
    {
        ASSERT(low > 0.0f);
        ASSERT(low <= high);
        m_TimeRange[0] = low;
        m_TimeRange[1] = high;
    }
    void Particle::Init()
    {
        EnableAngleLimite();
        SetAngleRangeX(0.0f, 2 * PI);
        SetAngleRangeY(0.0f, PI);
        SetVelocityRange(2.0f, 4.0f);
        SetTimeRange(0.2f, 0.5f);
        // dimension = 8
        // position 3
        // velocity 3
        // time     2
        int nSize = m_ParticleNum * (8 * sizeof(float));
        float* dataTemp = new float[nSize];
        float aVertex[8];
        for (int i = 0; i < m_ParticleNum; i++)
        {
            memset(aVertex, 0, 3 * sizeof(float));  // the begining position  0 1 2
            float randVelocity = GetRandFloat(m_VelocityRange);
            float randAngleX = GetRandFloat(m_AngleRangeX);
            float randAngleY = GetRandFloat(m_AngleRangeY);
            float sinY = sin(randAngleY) * randVelocity;
            aVertex[3] = sinY * cos(randAngleX);            // x velocity   3
            aVertex[4] = cos(randAngleY) * randVelocity;    // y velocity   4
            aVertex[5] = sinY * sin(randAngleX);            // z velocity   5
            aVertex[6] = GetRandFloat(m_TimeRange);         // time         6
            aVertex[7] = 0.f;                               // 7
            memcpy(dataTemp + m_ParticleNum * 8, aVertex, 8 * sizeof(float));
        }
        m_buffer.Init(nSize, dataTemp);
        delete[] dataTemp;
    }
}