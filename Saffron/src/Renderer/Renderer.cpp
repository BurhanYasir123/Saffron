#include "Renderer.h"

namespace Saffron
{
    const size_t MAX_VERTS = 10000; 
    const size_t MAX_INDICES = 20000;

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

        glGenVertexArrays(1, &gl_global_VAO);
        glBindVertexArray(gl_global_VAO);

        glGenBuffers(1, &gl_global_VB);
        glGenBuffers(1, &gl_global_IB);

        glBindBuffer(GL_ARRAY_BUFFER, gl_global_VB);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTS * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_global_IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);

        gl_shader_program_id = OpenGLShaders::LoadShaders("Vert.shader", "Frag.shader");

        SF_CORE_INFO_("Renderer initialized with OpenGL " << glGetString(GL_VERSION), "Renderer");
        isInitialized = true;
    }

    void Renderer::SetBackgroundColor(glm::vec3 color)
    {
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::InitTriangle(TriangleInfo info)
    {
        RenderInfo rinfo;
        rinfo.command = RenderCommand::TRIANGLE;
        rinfo.color = info.color;

        std::vector<float> vert_data = {
            info.point1.pos.x, info.point1.pos.y, info.point1.pos.z,
            info.color.r, info.color.g, info.color.b,
            info.point2.pos.x, info.point2.pos.y, info.point2.pos.z,
            info.color.r, info.color.g, info.color.b,
            info.point3.pos.x, info.point3.pos.y, info.point3.pos.z,
            info.color.r, info.color.g, info.color.b,
        };

        // SF_CORE_WARN(
        //     "::: " << 
        //     info.point1.pos.x << " " <<  info.point1.pos.y << " " <<  info.point1.pos.z << " : " << 
        //     info.point2.pos.x << " " <<  info.point2.pos.y << " " <<  info.point2.pos.z << " : " << 
        //     info.point3.pos.x << " " <<  info.point3.pos.y << " " <<  info.point3.pos.z
        // );
            

        std::vector<unsigned int> indicies;
        if(collectedIndicies.empty())
        {
            indicies = {0, 1, 2};
        } else {
            indicies = {
                collectedIndicies.back() + 1, 
                collectedIndicies.back() + 2, 
                collectedIndicies.back() + 3
            };
        }


        size_t vertexOffset = (collectedVerts.size() * sizeof(float));
        size_t indexOffset  = (collectedIndicies.size()* sizeof(unsigned int));
        
        glBindBuffer(GL_ARRAY_BUFFER, gl_global_VB);
        glBufferSubData(GL_ARRAY_BUFFER, vertexOffset,
                        vert_data.size() * sizeof(float),
                        vert_data.data());
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_global_IB);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexOffset,
                        indicies.size() * sizeof(unsigned int),
                        indicies.data());
        

        collectedVerts.insert(collectedVerts.end(), vert_data.begin(), vert_data.end());
        collectedIndicies.insert(collectedIndicies.end(), indicies.begin(), indicies.end());


        rinfo.VB = gl_global_VB;

        RenderQueue.push_back(rinfo);
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

        //bool demo = true;

        //ImGui::ShowDemoWindow(&demo);
    }
    
    void Renderer::EndFrame()
    {

        // SF_CORE_INFO(":::::: VERTS");
        // for(auto x : collectedVerts)
        // {
        //     SF_CORE_WARN(x);
        // } SF_CORE_INFO(":::::::");

        // SF_CORE_INFO(":::::: INDICIES");
        // for(auto x : collectedIndicies)
        // {
        //     SF_CORE_WARN(x);
        // } SF_CORE_INFO(":::::::");


        // Verts
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void*)0
        );
        glEnableVertexAttribArray(0);


        // Colors
        glVertexAttribPointer(
            1,
            3, 
            GL_FLOAT, 
            GL_FALSE, 
            6 * sizeof(float), 
            (void*)(3 * sizeof(float))
        );
        glEnableVertexAttribArray(1);

        // glBufferData(GL_ARRAY_BUFFER, collectedVerts.size() * sizeof(float), collectedVerts.data(), GL_DYNAMIC_DRAW);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, collectedIndicies.size() * sizeof(unsigned int), collectedIndicies.data(), GL_DYNAMIC_DRAW);

        glUseProgram(gl_shader_program_id);
        glBindVertexArray(gl_global_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_global_IB);
        glDrawElements(GL_TRIANGLES, collectedIndicies.size(), GL_UNSIGNED_INT, 0);


        //RenderQueue.clear();
        //collectedVerts.clear();
        //collectedIndicies.clear();
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

        //sleep_ms(10); //------------------------------------------------------------------------------------

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