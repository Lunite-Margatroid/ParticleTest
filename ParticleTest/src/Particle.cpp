#include "pch.h"
#include "Particle.h"
namespace ptt
{
    
    Particle::Particle(unsigned int program)
        :m_ParticleNum(300),
        m_BufferOffset(0),
        m_Program(program)
    {
        Init();
    }
    Particle::Particle(int nParticle)
        :m_ParticleNum(nParticle)
    {
        Init();
    }

    Particle::~Particle()
    {
    }

    // call before drawing
    int Particle::BindBufferFeedback()
    {
        static unsigned int size;
        size = m_ParticleNum * sizeof(float);
        if (m_BufferOffset == 0)
        {
            m_VAO[0].Bind();
            m_Feedback.BindBufferRange(0, m_buffer.GetID(), m_BufferOffset, size);
            m_BufferOffset = size;
            return 0;
        }
        else
        {
            m_VAO[1].Bind();
            m_Feedback.BindBufferRange(0, m_buffer.GetID(), m_BufferOffset, size);
            m_BufferOffset = 0;
            return 1;
        }
        return 0;
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

        // ------------------buffer init------------------
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

        // ----------------feedback init-------------------
        m_Feedback.PushVarying("u_T");
        m_Feedback.ApplyVarying(m_Program);

        // ---------------- vertex array init-------------
        m_VAO[0].SetVB(m_buffer.GetID());
        m_VAO[0].SetMetaType(GL_POINTS);
        m_VAO[0].PushAttrib<float>(1);      // time
        m_VAO[0].PushAttrib<float>(3);      // position
        m_VAO[0].PushAttrib<float>(3);      // velocity
        m_VAO[0].ApplyLayoutSeparate(m_ParticleNum);

        m_VAO[1].SetVB(m_buffer.GetID());
        m_VAO[1].SetMetaType(GL_POINTS);
        m_VAO[1].PushAttrib<float>(1, LM::AttribLayout::skip_arrtib);      // time 1
        m_VAO[1].PushAttrib<float>(1);      // time 2
        m_VAO[1].PushAttrib<float>(3);      // position
        m_VAO[1].PushAttrib<float>(3);      // velocity
        m_VAO[1].ApplyLayoutSeparate(m_ParticleNum);

    }
    void Particle::Draw()
    {
        static int index;
        index = BindBufferFeedback();
        m_Feedback.BeginTransformFeedback(GL_POINTS);
        m_VAO[index].DrawArray(m_ParticleNum);
        m_Feedback.EndTransformFeedback();
    }
}