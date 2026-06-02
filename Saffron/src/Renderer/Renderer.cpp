#include "Renderer.h"

namespace Saffron
{
	static GLFWwindow* s_Window = nullptr;

    static double lastTime;

	Renderer::Renderer(const char* window_title, int window_width, int window_height)
	{
		Init(window_title, window_width, window_height);
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	GLFWwindow* Renderer::GetWindowHandle()
	{
		return s_Window;
	}

    void Renderer::Init(const char* window_title, int window_width, int window_height) {
        if (!glfwInit()) {
            SF_CORE_ERR("Failed to init GLFW");
            return;
        }

        const char* glsl_version = "#version 130";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        s_Window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
        if (!s_Window) {
            SF_CORE_ERR("Failed to create window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(s_Window);

        glfwSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            SF_CORE_ERR("Failed to init GLAD");
            return;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(s_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);



        SF_CORE_INFO("Renderer initialized with OpenGL " << glGetString(GL_VERSION));
    }

    void Renderer::SetBackgroundColor(glm::vec3 color)
    {
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Renderer::BeginFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        lastTime = glfwGetTime();

        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();   

        // bool demo = true;

        // ImGui::ShowDemoWindow(&demo);
    }
    
    void Renderer::EndFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        double currentTime = glfwGetTime();
        io.DeltaTime = currentTime - lastTime;
        lastTime = currentTime;


        ImGui::Render();
        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        // glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());        

        glfwSwapBuffers(s_Window);
    }
    
    bool Renderer::ShouldEndLoop()
    {
        return glfwWindowShouldClose(s_Window);
    }


    void Renderer::Shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(s_Window);
        glfwTerminate();
        SF_CORE_INFO("Renderer shutdown!!!");
    }
}