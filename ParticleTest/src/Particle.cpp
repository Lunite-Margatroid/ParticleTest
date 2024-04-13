#include "pch.h"
#include "Particle.h"
namespace ptt
{
    Particle::Particle(LM::Shader* shader, int nParticle)
        :m_ParticleNum(nParticle),
        m_BufferOffset(0),
        m_Shader(shader),
        m_AngleLimite(false)
    {
        m_Program = m_Shader->GetShaderID();
        Init();
    }

    Particle::~Particle()
    {
    }

    // call before drawing
    int Particle::BindBufferFeedback()
    {
        static unsigned int size;
        size = m_ParticleNum * sizeof(float) * 7;
        if (m_BufferOffset == 0)
        {
            m_BufferOffset = size;
            m_VAO[0].Bind();    // front half to draw
            m_Feedback.BindBufferRange(0, m_buffer.GetID(), m_BufferOffset, size);  // back half to get feedback
            return 0;
        }
        else
        {
            m_BufferOffset = 0;
            m_VAO[1].Bind();
            m_Feedback.BindBufferRange(0, m_buffer.GetID(), m_BufferOffset, size);
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
        // dimension = 7
        // position 3
        // velocity 3
        // time     1
        int nSize = m_ParticleNum * (7 * sizeof(float)) * 2;
        float* dataTemp = new float[nSize];
        float aVertex[7];
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
            aVertex[6] = 0.0f;                              // time         6
            memcpy(dataTemp + i * 7, aVertex, 7 * sizeof(float));
            // dst ptr          res ptr             size
        }
        memcpy(dataTemp + (nSize >> 1), dataTemp, nSize >> 1);
        //memset(dataTemp, 0, nSize);
        m_buffer.Init(nSize, dataTemp);
        delete[] dataTemp;

        // ----------------feedback init-------------------
        m_Feedback.PushVarying("out_Pos");
        m_Feedback.PushVarying("out_Vel");
        m_Feedback.PushVarying("out_T");
        m_Feedback.ApplyVarying(m_Program);

        // ---------------- vertex array init-------------
        m_VAO[0].SetVB(m_buffer.GetID());
        m_VAO[0].SetMetaType(GL_POINTS);
        m_VAO[0].PushAttrib<float>(3);      // position
        m_VAO[0].PushAttrib<float>(3);      // velocity
        m_VAO[0].PushAttrib<float>(1);      // time
        m_VAO[0].ApplyLayout();

        m_VAO[1].SetVB(m_buffer.GetID());
        m_VAO[1].SetMetaType(GL_POINTS);
        m_VAO[1].PushAttrib<float>(3);      // position
        m_VAO[1].PushAttrib<float>(3);      // velocity
        m_VAO[1].PushAttrib<float>(1);      // time
        m_VAO[1].ApplyLayout(m_ParticleNum * 7 *sizeof(float));
    }
    void Particle::Update(float DeltaTime)
    {
        m_Shader->SetUniform1f("u_DeltaTime", DeltaTime);
    }
    void Particle::Draw()
    {
        static int index;
        index = BindBufferFeedback();
        m_Feedback.BeginTransformFeedback(GL_POINTS);
        m_VAO[index].DrawArray(m_ParticleNum);
        m_Feedback.EndTransformFeedback();
    }
    void Particle::PushAttrib(int dimension)
    {
    }
    void Particle::ApplyAttrib()
    {
    }
    void Particle::BindProgram(unsigned int program)
    {
    }
    void Particle::InitShaderUniform()
    {
        // ---------------- shader uniform init----------------
        m_Shader->SetUniform1f("u_MinVelocity", m_VelocityRange[0]);
        m_Shader->SetUniform1f("u_MaxVelocity", m_VelocityRange[1]);
        m_Shader->SetUniform1f("u_MinAngleX", m_AngleRangeX[0]);
        m_Shader->SetUniform1f("u_MaxAngleX", m_AngleRangeX[1]);
        m_Shader->SetUniform1f("u_MinAngleY", m_AngleRangeY[0]);
        m_Shader->SetUniform1f("u_MaxAngleY", m_AngleRangeY[1]);
        m_Shader->SetUniform1f("u_MinTime", m_TimeRange[0]);
        m_Shader->SetUniform1f("u_MaxTime", m_TimeRange[1]);
    }
}