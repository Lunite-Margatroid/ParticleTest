#pragma once
#include "Shader/Shader.h"
#include "Shader/tfbShader.h"
#include "Camera.h"
#include "Camera3D.h"
#include "glObj/Texture.h"
#include "TransparencySprite.h"
#include "glObj/oitContext.h"
#include "ElementBuffer.h"
namespace ptt
{
	class Renderer
	{
	public:
		enum class Shaders
		{
			FireWork, Hanabi, HanabiSpark, Mesh_V_N_T, QuadMesh, OIT, LightedMesh_V_N_T
		};
		enum class Cameras
		{
			Camera3D_Alpha
		};

		enum class VertexArrays
		{
			Quad_V_N_T, Cube_V_N_T
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

		bool m_oitRendering;
		bool m_oitRender;
		std::unique_ptr<oitContext> m_oitContext;
		std::queue<TransparencySprite> m_TransparencyRenderQueue;

		std::unordered_map<Shaders, LM::Shader*> m_ShaderMap;
		std::unordered_map<Shaders, LM::Shader*> m_oitShaderMap;
		std::unordered_map<Cameras, Camera*> m_CameraMap;
		std::unordered_map<std::string, LM::Texture*> m_Textures;

		std::vector<std::string> m_TextureComboName;

		LM::VertexBuffer m_VertexBuffer;
		LM::ElementBuffer m_ElementBuffer;
		std::unordered_map<VertexArrays, LM::VertexArray*> m_VertexArrayMap;

		Renderer();

		static Renderer* s_Instance;

		void InitShader();
		void InitTexture();
		void InitCamera();
		void InitOIT();
		void InitVertexArray();

		void OitRenderBegin();
		void OitRenderEnd();
	public:
		virtual ~Renderer();
		
		virtual void SetTransMat();

		void SetViewTrans(const glm::mat4& viewTrans);
		void SetModelTrans(const glm::mat4& modelTrans);
		void SetProjectionTrans(const glm::mat4& projectionTrans);

		

		static LM::Texture* LoadTexture(const std::string& path, LM::TextureType type = LM::texture_diffuse);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="texInd"> default:0 return the default texture while is fully white.</param>
		/// <returns></returns>
		static LM::Texture* GetTexture(const std::string& texName = "default texture");
		static const std::string& GetTextureComboName(int texCombo = 0);
		static unsigned int GetTextureCount();
		static const std::unordered_map<std::string, LM::Texture*>& GetTextureMap();

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

		static void RenderSprite(Sprite* sprite,const glm::mat4& modelTrans);
		static void RenderTransparencySprite();

		static oitContext* GetOITContext();

		static LM::VertexArray* GetVertexArray(VertexArrays va);
	};
}