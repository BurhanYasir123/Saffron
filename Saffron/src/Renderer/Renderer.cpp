#include "Renderer.h"
#include "Core.h"

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

        ImGuiInitInfo iginfo;
        iginfo.window = s_Window;
        iginfo.glsl_version = glsl_version;

        igRender.Init(iginfo);

        VB_offset = 0;
        IB_offset = 0;

        glGenVertexArrays(1, &gl_global_VAO);
        glBindVertexArray(gl_global_VAO);

        glGenBuffers(1, &gl_global_VB);
        glGenBuffers(1, &gl_global_IB);

        glBindBuffer(GL_ARRAY_BUFFER, gl_global_VB);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTS * sizeof(float), nullptr, GL_STREAM_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_global_IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(unsigned int), nullptr, GL_STREAM_DRAW);

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


        gl_shader_program_id = OpenGLShaders::LoadShaders("Vert.shader", "Frag.shader");

        SF_CORE_INFO_("Renderer initialized with OpenGL " << glGetString(GL_VERSION), "Renderer");
        isInitialized = true;
    }

    void Renderer::SetBackgroundColor(glm::vec3 color)
    {
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    int Renderer::DrawTriangle(TriangleInfo info)
    {
        RenderCommand cmd;
        cmd.type = MeshType::TRIANGLE;
        cmd.pos = info.pos;
        cmd.color = info.color;
        cmd.size = info.size;

        CommandQueue.push_back(cmd);

        return 0;
    }
    
    int Renderer::DrawRectangle(RectangleInfo info)
    {
        return 0;
    }

    void Renderer::BeginFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        lastTime = glfwGetTime();

        glfwPollEvents();

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

        for(auto cmd : CommandQueue)
        {
            switch (cmd.type) {
                case MeshType::TRIANGLE:
                    float vert_data[6*3] = {
                        cmd.pos.x, cmd.pos.y+(cmd.size/2), cmd.pos.z,
                        cmd.color.r, cmd.color.g, cmd.color.b,

                        cmd.pos.x-(cmd.size/2), cmd.pos.y-(cmd.size/2), cmd.pos.z,
                        cmd.color.r, cmd.color.g, cmd.color.b,

                        cmd.pos.x+(cmd.size/2), cmd.pos.y-(cmd.size/2), cmd.pos.z,
                        cmd.color.r, cmd.color.g, cmd.color.b, 
                    };
                    glBufferSubData(GL_ARRAY_BUFFER, VB_offset*sizeof(float), sizeof(vert_data), vert_data);
                    VB_offset += 18;

                    unsigned int index_data[3] = {
                        (unsigned int)( ( IB_offset - 1) + 1 ),
                        (unsigned int)( ( IB_offset - 1) + 2 ),
                        (unsigned int)( ( IB_offset - 1) + 3 )
                    };

                    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, IB_offset*sizeof(float), sizeof(index_data), index_data);
                    IB_offset += 3;

            }
        }

        glUseProgram(gl_shader_program_id);
        glBindVertexArray(gl_global_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_global_IB);
        glDrawElements(GL_TRIANGLES, IB_offset, GL_UNSIGNED_INT, 0);

        igRender.EndFrame();     

        glfwSwapBuffers(s_Window);

        CommandQueue.clear();
        VB_offset = 0;
        IB_offset = 0;

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
        igRender.Shutdown();

        glfwDestroyWindow(s_Window);
        glfwTerminate();
        SF_CORE_INFO_("Renderer shutdown!!!", "Renderer");
    }
}