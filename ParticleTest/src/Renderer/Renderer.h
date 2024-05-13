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
			FireWork, Hanabi, HanabiSpark, Mesh_V_N_T, QuadMesh
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

		glm::mat3 m_NormalTrans;

		LM::Shader* m_CurrentShader;
		Camera* m_CurrentCamera;

		std::unordered_map<Shaders, LM::Shader*> m_ShaderMap;
		std::unordered_map<Cameras, Camera*> m_CameraMap;
		std::vector<LM::Texture*> m_Textures;
		std::vector<std::string> m_TextureName;

		std::vector<std::string> m_TextureComboName;

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
		/// <summary>
		/// 
		/// </summary>
		/// <param name="texInd"> default:0 return the default texture while is fully white.</param>
		/// <returns></returns>
		static LM::Texture* GetTexture(unsigned int texInd = 0);
		static const std::string& GetTextureName(unsigned int texInd = 0);
		static const std::string& GetTextureComboName(int texCombo = 0);
		static unsigned int GetTextureCount();

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

		static glm::mat3& GetNormalTrans();
	};
}