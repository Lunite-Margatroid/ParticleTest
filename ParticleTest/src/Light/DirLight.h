#pragma once
#include "Light.h"
namespace LM
{
    class DirLight :
        virtual public Light
    {
        /* ˵��
        ��Ӧ��ɫ���ṹ
        // �����Դ
            struct DirLight
            {
                vec3 ambient;			// ������
                vec3 diffuse;			// ������
                vec3 specular;			// ���淴��

                vec3 direction;			// ���շ���
            };

        */
    protected:
        glm::vec3 m_v3Direction;

        
    public:
        DirLight(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir);
        DirLight();
        ~DirLight();
        void SetLightDirection(const glm::vec3& dir);
        void SetUniformLight(const std::string& valName, Shader& shader) override;
        void SetUniformDirection(const std::string& valName, Shader& shader);

        const glm::vec3& GetDirection() const;
    };
}

