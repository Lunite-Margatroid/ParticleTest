#pragma once
#include "Light.h"
namespace LM
{
    class DirLight :
        virtual public Light
    {
        /* 说明
        对应着色器结构
        // 定向光源
            struct DirLight
            {
                vec3 ambient;			// 环境光
                vec3 diffuse;			// 漫反射
                vec3 specular;			// 镜面反射

                vec3 direction;			// 光照方向
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

