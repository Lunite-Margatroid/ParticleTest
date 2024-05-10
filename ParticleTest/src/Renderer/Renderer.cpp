#include "pch.h"
#include "Renderer.h"

namespace ptt
{
	Renderer* Renderer::s_Instance = nullptr;

	Renderer::Renderer():
		m_ViewTrans(1.0f),
		m_ModelTrans(1.0f),
		m_ProjectionTrans(1.0f),
		m_CurrentShader(nullptr),
		m_CurrentCamera(nullptr)
	{
		InitShader();
		InitCamera();
		InitTexture();
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
	}
	void Renderer::InitTexture()
	{
		m_Textures.push_back(new LM::Texture());
	}
	void Renderer::InitCamera()
	{
		m_CameraMap[Cameras::Camera3D_Alpha] = new Camera3D();
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
		for (LM::Texture* tex : m_Textures)
		{
			delete tex;
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
	unsigned int Renderer::LoadTexture(const std::string& path, LM::TextureType type)
	{
		auto& textures =  GetInstance()->m_Textures;
		unsigned int ret = textures.size();
		textures.push_back(new LM::Texture(path, type));

		return ret;
	}
	LM::Texture* Renderer::GetTexture(unsigned int texInd)
	{
		auto& textures = GetInstance()->m_Textures;
		if(texInd >= textures.size())
			return nullptr;
		return textures[texInd];
	}
	LM::Shader* Renderer::GetShader(Shaders shader)
	{
		auto& map = GetInstance()->m_ShaderMap;
		if (map.find(shader) == map.end())
			return nullptr;
		return map[shader];
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
}