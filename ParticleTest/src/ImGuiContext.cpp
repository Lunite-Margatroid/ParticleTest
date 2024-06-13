#include "pch.h"
#include "ImGuiContext.h"

namespace ptt
{
    ImGuiContext* ImGuiContext::s_Instance = nullptr;

	void ImGuiContext::Init(GLFWwindow* window)
	{
        m_Init = true;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        const char* glsl_version = "#version 450 core";
        ImGui_ImplOpenGL3_Init(glsl_version);

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/simhei.ttf", 20, NULL, io.Fonts->GetGlyphRangesChineseFull());

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);

        m_ImGuiWindows["Style Editor"] = new StyleEditor("Style Editor");
        m_ImGuiWindows["Style Editor"]->CloseWindow();

        m_DialogManager.GenDialog<TextureLoadDialog>("Texture Load");
        
	}
    void ImGuiContext::Terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        for (auto& windows : m_ImGuiWindows)
        {
            delete windows.second;
        }
    }
    ImGuiContext::ImGuiContext():
         m_Init(false)
    {
        ASSERT(s_Instance == nullptr);
        s_Instance = this;
    }
    ImGuiContext::~ImGuiContext()
    {
        Terminate();
    }
    void ImGuiContext::ImGuiBegin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // docking place
        ImGui::DockSpaceOverViewport();

        UpdateDialogID();
    }
    void ImGuiContext::ImGuiEnd()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiContext::Popup(const std::string& name)
    {
        m_DialogManager.Popup(name);
    }

    void ImGuiContext::UpdateDialogID()
    {
        m_DialogManager.Update();
    }

    void ImGuiContext::ShowDialog(const std::string& name)
    {
        m_DialogManager.ShowWindow(name);
    }

    void ImGuiContext::SaveStyle(const std::string& fileName)
    {
        ASSERT(s_Instance);
        std::ofstream outFile;
        outFile.open(fileName, std::ios::binary);
        if (!outFile.is_open())
        {
            std::cout << "can't open file: " << fileName << std::endl;
            return;
        }
        ImGuiStyle* style = &ImGui::GetStyle();
        int size = sizeof(ImGuiStyle);
        ASSERT(sizeof(int) == 4);
        outFile.write((char*)&size, sizeof(int));
        outFile.write((char*)style, size);
        outFile.close();
    }
    void ImGuiContext::LoadStyle(const std::string& fileName)
    {
        ASSERT(s_Instance);
        std::ifstream inFile;
        inFile.open(fileName, std::ios::binary);
        if (!inFile.is_open())
        {
            std::cout << "can't open file: " << fileName << std::endl;
            return;
        }
        ImGuiStyle* style = &ImGui::GetStyle();
        int size = sizeof(ImGuiStyle);
        ASSERT(sizeof(int) == 4);
        int tSize;
        inFile.read((char*)&tSize, sizeof(int));
        if (tSize != size)
        {
            std::cout << "Version not matchs.\n";
            inFile.close();
            return;
        }
        inFile.read((char*)style, size);
        inFile.close();

    }
    void ImGuiContext::ShowWindow(const std::string& keyString)
    {
        std::unordered_map<std::string, ImGuiWindows*>& windows = GetInstance()->m_ImGuiWindows;
        if (windows.find(keyString) != windows.end())
        {
            ImGuiWindows* window = windows[keyString];
            if (window->IsOpen())
                window->ShowWindow();
        }
    }
    void ImGuiContext::OpenWindow(const std::string& keyString)
    {
        std::unordered_map<std::string, ImGuiWindows*>& windows = GetInstance()->m_ImGuiWindows;
        if (windows.find(keyString) != windows.end())
        {
            ImGuiWindows* window = windows[keyString];
            window->OpenWindow();
        }
    }
    void ImGuiContext::CloseWindow(const std::string& keyString)
    {
        std::unordered_map<std::string, ImGuiWindows*>& windows = GetInstance()->m_ImGuiWindows;
        if (windows.find(keyString) != windows.end())
        {
            ImGuiWindows* window = windows[keyString];
            window->CloseWindow();
        }
    }
    ImGuiContext* ImGuiContext::GetInstance()
    {
        ASSERT(s_Instance);
        return s_Instance;
    }
}