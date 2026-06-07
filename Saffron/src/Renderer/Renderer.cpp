#include "Renderer.h"

namespace Saffron
{
    void sleep_ms(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

	static GLFWwindow* s_Window = nullptr;

    static double lastTime;

	Renderer::Renderer(RendererInitInfo info)
	{
		Init(info);
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	GLFWwindow* Renderer::GetWindowHandle()
	{
		return s_Window;
	}

    void Renderer::Init(RendererInitInfo info) {
        if (!glfwInit()) {
            SF_CORE_ERR_("Failed to init GLFW", "Renderer");
            return;
        }

        SF_CORE_INFO_("GLFW inttialized!", "Renderer");

        const char* glsl_version = "#version 130";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        s_Window = glfwCreateWindow(info.window_width, info.window_height, info.window_title, nullptr, nullptr);
        if (!s_Window) {
            SF_CORE_ERR_("Failed to create window", "Renderer");
            glfwTerminate();
            return;
        }

        SF_CORE_INFO_("Window Created!!", "Renderer");

        glfwMakeContextCurrent(s_Window);

        glfwSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            SF_CORE_ERR_("Failed to init GLAD", "Renderer");
            return;
        }

        SF_CORE_INFO_("GLFW Context and Glad initialized!!", "Renderer");

        // IMGUI_CHECKVERSION();
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();

        // ImGui_ImplGlfw_InitForOpenGL(s_Window, true);
        // ImGui_ImplOpenGL3_Init(glsl_version);
        ImGuiInitInfo iginfo;
        iginfo.window = s_Window;
        iginfo.glsl_version = glsl_version;

        igRender.Init(iginfo);

        SF_CORE_INFO_("Renderer initialized with OpenGL " << glGetString(GL_VERSION), "Renderer");
        isInitialized = true;
    }

    void Renderer::SetBackgroundColor(glm::vec3 color)
    {
        // glClearColor(color.r, color.g, color.b, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        RenderInfo info;
        info.command = RenderCommand::SCREEN_CLEAR;
        info.color = color;

        RenderQueue.push_back(info);
    }
    
    void Renderer::BeginFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        lastTime = glfwGetTime();

        glfwPollEvents();
        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();   

        igRender.BeginFrame();

        // bool demo = true;

        // ImGui::ShowDemoWindow(&demo);
    }
    
    void Renderer::EndFrame()
    {
        // non-optimized commands
        for(auto& command : RenderQueue)
        {
            if(command.command == RenderCommand::SCREEN_CLEAR)
            {
                //SF_CORE_WARN("Clear color");
                glClearColor(command.color.r, command.color.g, command.color.b, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                command.command == RenderCommand::NULL_COMMAND;
            }
        }

        // optimized commands
        // if(RenderQueue != LastRenderQueue)
        // {
        //     for(auto comamnd : RenderQueue)
        //     {
        //         if(command.command == RenderCommand::TRIANGLE)
        //         {
    
        //         }
        //     }
        // }
        // LastRenderQueue = RenderQueue;


        RenderQueue.clear();
        // ImGui::Render();
        // // int display_w, display_h;
        // // glfwGetFramebufferSize(window, &display_w, &display_h);
        // // glViewport(0, 0, display_w, display_h);
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());   
        igRender.EndFrame();     

        glfwSwapBuffers(s_Window);

        ImGuiIO& io = ImGui::GetIO();
        double currentTime = glfwGetTime();
        io.DeltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sleep_ms(10); //------------------------------------------------------------------------------------

    }
    
    bool Renderer::ShouldEndLoop()
    {
        return glfwWindowShouldClose(s_Window);
    }


    void Renderer::Shutdown() {
        //ImGui_ImplOpenGL3_Shutdown();
        //ImGui_ImplGlfw_Shutdown();
        //ImGui::DestroyContext();
        igRender.Shutdown();

        glfwDestroyWindow(s_Window);
        glfwTerminate();
        SF_CORE_INFO_("Renderer shutdown!!!", "Renderer");
    }
}