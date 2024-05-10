#pragma once
#include "Shader/Shader.h"
#include "Shader/tfbShader.h"
#include "Camera.h"
#include "Camera3D.h"
#include "glObj/Texture.h"
namespace ptt
{
	class Renderer
	{
	public:
		enum class Shaders
		{
			FireWork, Hanabi, HanabiSpark, QuadMesh
		};
		enum class Cameras
		{
			Camera3D_Alpha
		};

	protected:
		glm::mat4 m_ViewTrans;
		glm::mat4 m_ModelTrans;
		glm::mat4 m_ProjectionTrans;

		glm::mat4 m_MVPTrans;
		glm::mat4 m_MVTrans;

		LM::Shader* m_CurrentShader;
		Camera* m_CurrentCamera;

		std::unordered_map<Shaders, LM::Shader*> m_ShaderMap;
		std::unordered_map<Cameras, Camera*> m_CameraMap;
		std::vector<LM::Texture*> m_Textures;
		Renderer();

		static Renderer* s_Instance;

		void InitShader();
		void InitTexture();
		void InitCamera();
	public:
		virtual ~Renderer();
		
		virtual void SetTransMat();

		void SetViewTrans(const glm::mat4& viewTrans);
		void SetModelTrans(const glm::mat4& modelTrans);
		void SetProjectionTrans(const glm::mat4& projectionTrans);

		static unsigned int LoadTexture(const std::string& path, LM::TextureType type = LM::texture_diffuse);
		static LM::Texture* GetTexture(unsigned int texInd);
		static LM::Shader* GetShader(Shaders shaderName);
		static void LoadShader(Shaders shaderName,const std::string& vertexShaderPath, const std::string& FragmentShaderPath);
		static void LoadShader(Shaders shaderName, const std::string& vertexShaderPath, const std::string& FragmentShaderPath, const std::string& GeometryShaderPath);

		static Camera* GetCamera(Cameras cameraName);
		static void LoadCamera(Cameras cameraName, Camera* camera);

		static void SetCurrentShader(LM::Shader* shader);
		static void SetCurrentCamera(Camera* camera);

		static Renderer* GetInstance();

		static LM::Shader* GetCurrentShader();
		static Camera* GetCurrentCamera();

		static glm::mat4& GetViewTrans();
		static glm::mat4& GetModelTrans();
		static glm::mat4& GetProjectionTrans();

		static glm::mat4& GetMVPTrans();
		static glm::mat4& GetMVTrans();
	};
}