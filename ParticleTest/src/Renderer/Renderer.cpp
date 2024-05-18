#include "pch.h"
#include "Renderer.h"
#include "Application.h"

namespace ptt
{
	Renderer* Renderer::s_Instance = nullptr;


	Renderer::Renderer():
		m_ViewTrans(1.0f),
		m_ModelTrans(1.0f),
		m_ProjectionTrans(1.0f),
		m_NormalTrans(1.0f),
		m_CurrentShader(nullptr),
		m_CurrentCamera(nullptr),
		m_oitContext(nullptr),
		m_oitRender(true)
	{
		InitShader();
		InitCamera();
		InitTexture();
		if(m_oitRender)
			InitOIT();
	}

	void Renderer::InitShader()
	{
		tfbShader* shader = new tfbShader("./res/shader/FireworkVertex.shader", "./res/shader/FireworkFrag.shader");
		m_ShaderMap[Shaders::FireWork] = dynamic_cast<LM::Shader*>(shader);
		shader->PushVarying("out_Pos");
		shader->PushVarying("out_Vel");
		shader->PushVarying("out_T");
		shader->ApplyVarying();

		shader = new tfbShader("./res/shader/HanabiSparkVertex.shader", "./res/shader/HanabiSparkFrag.shader");
		m_ShaderMap[Shaders::HanabiSpark] = dynamic_cast<LM::Shader*>(shader);
		shader->PushVarying("out_Pos");
		shader->PushVarying("out_Vel");
		shader->PushVarying("out_T");
		shader->ApplyVarying();

		shader = new tfbShader("./res/shader/HanabiVertex.shader", "./res/shader/HanabiFrag.shader");
		m_ShaderMap[Shaders::Hanabi] = dynamic_cast<LM::Shader*>(shader);
		shader->PushVarying("out_Pos");
		shader->PushVarying("out_T");
		shader->PushVarying("out_Vel");
		shader->PushVarying("gl_SkipComponents1");
		shader->ApplyVarying();

		LM::Shader* shd = new LM::Shader("./res/shader/QuadMeshSpriteVertex.shader", "./res/shader/QuadMeshSpriteFrag.shader");
		m_ShaderMap[Shaders::QuadMesh] = dynamic_cast<LM::Shader*>(shd);

		shd = new LM::Shader("./res/shader/MeshVertex.shader", "./res/shader/MeshFrag.shader");
		m_ShaderMap[Shaders::Mesh_V_N_T] = dynamic_cast<LM::Shader*>(shd);
		shd = new LM::Shader("./res/shader/MeshVertex.shader", "./res/shader/MeshFrag_oit.shader");
		m_oitShaderMap[Shaders::Mesh_V_N_T] = dynamic_cast<LM::Shader*>(shd);

		shd = new LM::Shader("./res/shader/OIT_Vertex.shader", "./res/shader/OIT_Fragment.shader");
		m_ShaderMap[Shaders::OIT] = dynamic_cast<LM::Shader*>(shd);
	}
	void Renderer::InitTexture()
	{
		LM::Texture* tex = new LM::Texture();
		tex->SetTextureName("default texture");
		m_Textures[tex->GetTextureName()] =  tex;
	}
	void Renderer::InitCamera()
	{
		m_CameraMap[Cameras::Camera3D_Alpha] = new Camera3D();
	}
	void Renderer::InitOIT()
	{
		m_oitContext = std::make_unique<oitContext>();
	}
	Renderer::~Renderer()
	{
		for (auto& shader : m_ShaderMap)
		{
			delete shader.second;
		}
		for (auto& camera : m_CameraMap)
		{
			delete camera.second;
		}
		for (auto& p : m_Textures)
		{
			delete p.second;
		}
	}
	void Renderer::SetTransMat()
	{
	}
	void Renderer::SetViewTrans(const glm::mat4& viewTrans)
	{
	}
	void Renderer::SetModelTrans(const glm::mat4& modelTrans)
	{
	}
	void Renderer::SetProjectionTrans(const glm::mat4& projectionTrans)
	{
	}
	void Renderer::OitRenderBegin()
	{
		m_oitRendering = true;
	}
	void Renderer::OitRenderEnd()
	{
		m_oitRendering = false;
	}
	LM::Texture* Renderer::LoadTexture(const std::string& path, LM::TextureType type)
	{
		auto& textures =  GetInstance()->m_Textures;
		//-----------------Get file name------------
		std::string::const_iterator begin;
		auto i = path.begin();
		for (; i != path.end(); i++)
		{
			if (*i == '\\' || *i == '/')
			{
				begin = i;
			}
		}
		begin++;
		std::string fileName('\n', 128);
		std::copy(begin, i, fileName.begin());
		//----------------------²éÖØ-------------------
		while (true)
		{
			if (textures.find(fileName) == textures.end())
			{
				break;
			}
			else
			{
				fileName.append("-");
			}
		}
		// ------------------------------
		LM::Texture* tex = new LM::Texture(path, type);
		tex->SetTextureName(std::move(fileName));
		textures[tex->GetTextureName()] = tex;
		return tex;
	}
	LM::Texture* Renderer::GetTexture(const std::string& texName)
	{
		auto& textures = GetInstance()->m_Textures;
		if (textures.find(texName) == textures.end())
		{
			return textures["default texture"];
		}
		return textures[texName];
	}
	const std::string& Renderer::GetTextureComboName(int texCombo)
	{
		Renderer* renderer = GetInstance();
		std::vector<std::string>& names = renderer->m_TextureComboName;
		if (texCombo + 1 <= names.size())
		{
			return names[texCombo];
		}
		
		std::string temp = "texture ";
		int i = names.size();
		for (; i < 100 && i <= texCombo; i++)
		{
			std::string tt = std::to_string(i);
			names.push_back(temp + tt);
		}
		return names[i-1];
	}
	unsigned int Renderer::GetTextureCount()
	{
		return (GetInstance()->m_Textures).size();
	}
	const std::unordered_map<std::string, LM::Texture*>& Renderer::GetTextureMap()
	{
		return GetInstance()->m_Textures;
	}
	LM::Shader* Renderer::GetShader(Shaders shader)
	{
		Renderer* render = GetInstance();
		auto& shaderMap = render->m_ShaderMap;
		auto& oitShaderMap = render->m_oitShaderMap;
		if (render->m_oitRendering)
		{
			if (oitShaderMap.find(shader) != oitShaderMap.end())
			{
				return oitShaderMap[shader];
			}
		}
		if (shaderMap.find(shader) == shaderMap.end())
			return nullptr;
		return shaderMap[shader];
	}
	void Renderer::LoadShader(Shaders shaderName, const std::string& vertexShaderPath, const std::string& FragmentShaderPath)
	{
		auto& map = GetInstance()->m_ShaderMap;
		if (map.find(shaderName) == map.end()) // not exist
		{
			map[shaderName] = new LM::Shader(vertexShaderPath, FragmentShaderPath);
		}
		else // exist
		{
			delete map[shaderName];
			map[shaderName] = new LM::Shader(vertexShaderPath, FragmentShaderPath);
		}
	}
	void Renderer::LoadShader(Shaders shaderName, const std::string& vertexShaderPath, const std::string& FragmentShaderPath, const std::string& GeometryShaderPath)
	{
		auto& map = GetInstance()->m_ShaderMap;
		if (map.find(shaderName) == map.end()) // not exist
		{
			map[shaderName] = new LM::Shader(vertexShaderPath, FragmentShaderPath, GeometryShaderPath);
		}
		else // exist
		{
			delete map[shaderName];
			map[shaderName] = new LM::Shader(vertexShaderPath, FragmentShaderPath, GeometryShaderPath);
		}
	}
	Camera* Renderer::GetCamera(Cameras cameraName)
	{
		auto& map = GetInstance()->m_CameraMap;
		if (map.find(cameraName) == map.end())
			return nullptr;
		return map[cameraName];
	}
	void Renderer::LoadCamera(Cameras cameraName, Camera* camera)
	{
		auto& map = GetInstance()->m_CameraMap;
		if (map.find(cameraName)== map.end())
		{
			map[cameraName] = camera;
		}
		else
		{
			delete map[cameraName];
			map[cameraName] = camera;
		}
	}
	void Renderer::SetCurrentShader(LM::Shader* shader)
	{
		GetInstance()->m_CurrentShader = shader;
		shader->Bind();
	}
	void Renderer::SetCurrentCamera(Camera* camera)
	{
		GetInstance()->m_CurrentCamera = camera;
	}
	Renderer* Renderer::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Renderer();
			return s_Instance;
		}
		return s_Instance;
	}
	LM::Shader* Renderer::GetCurrentShader()
	{
		return GetInstance()->m_CurrentShader;
	}
	Camera* Renderer::GetCurrentCamera()
	{
		return GetInstance()->m_CurrentCamera;
	}
	glm::mat4& Renderer::GetViewTrans()
	{
		// TODO: insert return statement here
		return GetInstance()->m_ViewTrans;
	}

	glm::mat4& Renderer::GetModelTrans()
	{
		// TODO: insert return statement here
		return GetInstance()->m_ModelTrans;
	}
	glm::mat4& Renderer::GetProjectionTrans()
	{
		// TODO: insert return statement here
		return GetInstance()->m_ProjectionTrans;
	}
	glm::mat4& Renderer::GetMVPTrans()
	{
		// TODO: insert return statement here
		return GetInstance()->m_MVPTrans;
	}
	glm::mat4& Renderer::GetMVTrans()
	{
		// TODO: insert return statement here
		return GetInstance()->m_MVTrans;
	}
	glm::mat3& Renderer::GetNormalTrans()
	{
		return GetInstance()->m_NormalTrans;
	}
	void Renderer::RenderSprite(Sprite* sprite, const glm::mat4& modelTrans)
	{
		if (sprite->IsTransparency())
			GetInstance()->m_TransparencyRenderQueue.emplace(TransparencySprite(sprite, modelTrans));
		else
			sprite->Render(modelTrans);
	}
	void Renderer::RenderTransparencySprite()
	{
		glDepthMask(GL_FALSE);

		Renderer* render = GetInstance();
		std::queue<TransparencySprite>& renderQueue = render->m_TransparencyRenderQueue;
		if (render->m_oitContext && render->m_oitRender)
		{
			//LM::FrameBuffer* currentFramebuffer = Application::GetCurrentFramebuffer();
			//LM::FrameBuffer* framebuffer = Application::GetFramebuffer();
			//framebuffer->Bind();
			render->OitRenderBegin();
			render->m_oitContext->RenderPreproc();
			while (!renderQueue.empty())
			{
				renderQueue.front()();
				renderQueue.pop();
			}
			render->OitRenderEnd();
			//currentFramebuffer->Bind();
			//render->m_oitContext->Render();
		}
		else
		{
			while (!renderQueue.empty())
			{
				renderQueue.front()();
				renderQueue.pop();
			}
		}

		glDepthMask(GL_TRUE);
	}
	oitContext* Renderer::GetOITContext()
	{
		return (GetInstance()->m_oitContext).get();
	}
}