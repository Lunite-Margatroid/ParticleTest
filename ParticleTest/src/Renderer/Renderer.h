#pragma once
#include "Shader/Shader.h"
#include "Shader/tfbShader.h"
#include "Camera.h"
#include "Camera3D.h"
#include "glObj/Texture.h"
#include "TransparencySprite.h"
#include "glObj/oitContext.h"
#include "ElementBuffer.h"
#include "Sprite/SkyboxSprite.h"
namespace ptt
{
	class Renderer
	{
	public:
		enum class Cameras
		{
			Camera3D_Alpha
		};

		enum class VertexArrays
		{
			Quad_P_N_T_TG, Cube_P_N_T_TG, Sphere_P_T_TG
		};

		std::unordered_map<LM::Shaders, std::string> Shader_Names;

	protected:
		glm::mat4 m_ViewTrans;
		glm::mat4 m_ModelTrans;
		glm::mat4 m_ProjectionTrans;

		glm::mat4 m_MVPTrans;
		glm::mat4 m_MVTrans;

		glm::mat3 m_NormalTrans;

		LM::Shader* m_CurrentShader;// ��ǰ��ɫ��
		Camera* m_CurrentCamera;	// ��ǰ�����
		
		bool m_oitRendering;		// ���ڽ��а�͸��������Ⱦ
		bool m_oitRender;			// �Ƿ���oit
		std::unique_ptr<oitContext> m_oitContext;	// oit context

		std::queue<TransparencySprite> m_TransparencyRenderQueue;	// ��͸��������Ⱦ���� ����պ�֮����Ⱦ

		std::queue<SkyboxSprite*> m_SkyboxRendererQueue;			// ��պ���Ⱦ���� �ڷ�͸������֮����Ⱦ

		std::unordered_map<LM::Shaders, LM::Shader*> m_ShaderMap;	// �Ѽ��ص���ɫ��
		std::unordered_map<LM::Shaders, LM::Shader*> m_oitShaderMap;// oit�汾����ɫ��
		std::unordered_map<Cameras, Camera*> m_CameraMap;			// �Ѽ��ص������
		std::unordered_map<std::string, LM::Texture*> m_Textures;	// �Ѽ��ص�����

		std::vector<std::string> m_TextureComboName;				// ��ȾGUI����ѡ��combo��ʹ�õļ�ֵ

		LM::VertexBuffer m_VertexBuffer;							// ����Ԥ��mesh�Ķ��㻺��
		LM::ElementBuffer m_ElementBuffer;							// ����Ԥ��mesh�Ķ��㻺��
		std::unordered_map<VertexArrays, LM::VertexArray*> m_VertexArrayMap;	// ���������ӳ��

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

		

		static LM::Texture* LoadTexture(const std::string& path, LM::TextureType type = LM::texture_diffuse, bool skipIfSame = false,
			GLenum dstColorMode = GL_RGB, GLenum srcColorMode = GL_RGB,
			GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR, GLenum wrap = GL_REPEAT, bool yReverse = true);
		static void SaveTexture(LM::Texture* texture);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="texInd"> default:0 return the default texture while is fully white.</param>
		/// <returns></returns>
		static LM::Texture* GetTexture(const std::string& texName = "default texture");
		static const std::string& GetTextureComboName(int texCombo = 0);
		static unsigned int GetTextureCount();
		static const std::unordered_map<std::string, LM::Texture*>& GetTextureMap();

		static LM::Shader* GetShader(LM::Shaders shaderName);
		static void LoadShader(LM::Shaders shaderName,const std::string& vertexShaderPath, const std::string& FragmentShaderPath);
		static void LoadShader(LM::Shaders shaderName, const std::string& vertexShaderPath, const std::string& FragmentShaderPath, const std::string& GeometryShaderPath);

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

		static const std::string& GetShaderName(LM::Shaders shaderName);
		static std::unordered_map<LM::Shaders, std::string>& GetShaderNames();

		static void PushSkyboxSprite(SkyboxSprite* skybox);
		static void RendererSkybox();
	};
}