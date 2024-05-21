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
		InitVertexArray();
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

		shd = new LM::Shader("./res/shader/LightedMeshVertex.shader", "./res/shader/LightedMeshFrag.shader");
		m_ShaderMap[Shaders::LightedMesh_V_N_T] = shd;
		shd = new LM::Shader("./res/shader/LightedMeshVertex.shader", "./res/shader/LightedMeshFrag_oit.shader");
		m_oitShaderMap[Shaders::LightedMesh_V_N_T] = dynamic_cast<LM::Shader*>(shd);
	}
	void Renderer::InitTexture()
	{
		LM::Texture* tex = new LM::Texture();
		tex->SetTextureName("default texture");
		m_Textures[tex->GetTextureName()] =  tex;

		tex = new LM::Texture(LM::texture_normal);
		tex->SetTextureName("default normal texture");
		m_Textures[tex->GetTextureName()] = tex;

		tex = new LM::Texture(LM::texture_specular);
		tex->SetTextureName("default specular texture");
		m_Textures[tex->GetTextureName()] = tex;

		tex = new LM::Texture(LM::texture_parallax);
		tex->SetTextureName("default parallax texture");
		m_Textures[tex->GetTextureName()] = tex;
	}
	void Renderer::InitCamera()
	{
		m_CameraMap[Cameras::Camera3D_Alpha] = new Camera3D();
	}
	void Renderer::InitOIT()
	{
		m_oitContext = std::make_unique<oitContext>();
	}
	void Renderer::InitVertexArray()
	{
		size_t totalSize = 0;
		size_t quadBufferSize = 4 * 8 * sizeof(float);
		size_t cubeBufferSize = 4 * 6 * 8 * sizeof(float);
		totalSize += quadBufferSize + cubeBufferSize;

		size_t eleBufferCount = 0;
		size_t cubeEleBufferCount = 36;

		eleBufferCount += cubeEleBufferCount;
		float vertice[]
		{
			// ---------------------- Quad ---------------------------------
			// postion float 3		normal vec float3    texture coordiate float 2
			-1.0f, 0.0f, -1.0f,   0.0f, 1.0f,0.0f,		0.0f, 0.0f,
			1.0f, 0.0f, -1.0f,   0.0f, 1.0f,0.0f,		1.0f, 0.0f,
			1.0f, 0.0f, 1.0f,   0.0f, 1.0f,0.0f,		1.0f, 1.0f,
			-1.0f, 0.0f, 1.0f,   0.0f, 1.0f,0.0f,		0.0f, 1.0f,

			// ----------------------- Cube --------------------------------
			// 位置坐标					法线向量					纹理坐标
			-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			0.0f, 0.0f,
			1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			0.0f, 1.0f,

			-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,			0.0f, 0.0f,
			-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			1.0f, 0.0f,
			1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			0.0f, 1.0f,

			-1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,			0.0f, 0.0f,
			-1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,			1.0f, 0.0f,
			1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,			1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,			0.0f, 1.0f,

			-1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,			0.0f, 0.0f,
			1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,			1.0f, 0.0f,
			1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,			1.0f, 1.0f,
			-1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,			0.0f, 1.0f,

			1.0f,-1.0f, -1.0f,		1.0f, 0.0f,  0.0f,			0.0f, 0.0f,
			1.0f,1.0f, -1.0f,		1.0f, 0.0f,  0.0f,			1.0f, 0.0f,
			1.0f,1.0f, 1.0f,		1.0f, 0.0f,  0.0f,			1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,		1.0f, 0.0f,  0.0f,			0.0f, 1.0f,

			-1.0f,-1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,			0.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,			1.0f, 0.0f,
			-1.0f,1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,			1.0f, 1.0f,
			-1.0f,1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,			0.0f, 1.0f
		};

		unsigned int indices[] =
		{
		0, 1,2,0,2,3,
		4,5,6, 4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20, 21,22,20,22,23
		};

		m_VertexBuffer.Init(totalSize, vertice, GL_STATIC_DRAW);
		m_ElementBuffer.Init(eleBufferCount, indices, GL_STATIC_DRAW);

		// quad
		LM::VertexArray* va = new LM::VertexArray();
		va->SetVB(m_VertexBuffer.GetID());
		va->SetCount(4);
		va->SetMetaType(GL_TRIANGLE_FAN);
		va->PushAttrib<float>(3);
		va->PushAttrib<float>(3);
		va->PushAttrib<float>(2);
		va->ApplyLayout(0);
		m_VertexArrayMap[VertexArrays::Quad_V_N_T] = va;

		// cube
		va = new LM::VertexArray();
		va->SetVB(m_VertexBuffer.GetID());
		va->SetEB(m_ElementBuffer.GetID());
		va->SetMetaType(GL_TRIANGLES);
		va->SetCount(36);
		va->SetElementOffset(0);
		va->PushAttrib<float>(3);
		va->PushAttrib<float>(3);
		va->PushAttrib<float>(2);
		va->ApplyLayout(quadBufferSize);
		m_VertexArrayMap[VertexArrays::Cube_V_N_T] = va;
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
		for (auto& va : m_VertexArrayMap)
		{
			delete va.second;
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
		char tempStr[128];
		memset(tempStr, 0, 128);
		int index = 0;
		for (; begin != path.end(); begin++)
		{
			tempStr[index] = *begin;
			index++;
		}
		tempStr[index] = '\0';
		std::string fileName(tempStr);
		//----------------------查重-------------------
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
	LM::VertexArray* Renderer::GetVertexArray(VertexArrays va)
	{
		std::unordered_map<VertexArrays, LM::VertexArray*> &vaMap = GetInstance()->m_VertexArrayMap;
		if (vaMap.find(va) == vaMap.end())
			return nullptr;
		return vaMap[va];
	}
}