#include "Renderer.h"
#include "Core.h"
#include "Log.h"
#include "Renderer/Camera.h"
#include "Util.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <numeric>

namespace Saffron
{
    const size_t MAX_VERTS = 10000; 
    const size_t MAX_INDICES = 20000;

    void sleep_ms(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

	static GLFWwindow* s_Window = nullptr;
    static double lastTime;

    static Camera* _renderer_cam = new Camera;

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

        win_w = info.window_width; win_h = info.window_height;
        aspect_ratio = (float)win_h / (float)win_w;

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

        gl_Uniforms["Shader_uAspectFix_X"] = glGetUniformLocation(gl_shader_program_id, "uAspectFix_X");
        gl_Uniforms["VP"] = glGetUniformLocation(gl_shader_program_id, "VP");

        CameraConfigInfo caminfo;
        caminfo.FOV = 45.0f;
        caminfo.pos = { 0.0f, 0.0f, -3.0f };
        caminfo.window_width = win_w;
        caminfo.window_height = win_h;

        _renderer_cam->ConfigCamera(caminfo);
        DefaultCamera = true;

        SF_CORE_INFO_("Renderer initialized with OpenGL " << glGetString(GL_VERSION), "Renderer");
        isInitialized = true;
    }

    void Renderer::RegisterCamera(Camera* cam)
    {
        if(!cam->IsConfigured())
        {
            SF_CORE_ERR_("Camera Not Configured before Registration", "Renderer");
            return;
        }
        DefaultCamera = false;
        delete _renderer_cam;
        _renderer_cam = cam;
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
        cmd.pos = Util::SC_to_NC(win_w, win_h, info.pos);
        cmd.color = info.color;
        cmd.size = Util::Single_SC_to_NC(win_h, info.size);

        CommandQueue.push_back(cmd);

        return 0;
    }
    
    int Renderer::DrawRectangle(RectangleInfo info)
    {
        RenderCommand cmd;
        cmd.type = MeshType::RECTANGLE;
        cmd.pos = Util::SC_to_NC(win_w, win_h, info.pos);
        cmd.color = info.color;
        cmd.h = Util::Single_SC_to_NC(win_h, info.height);
        cmd.w = Util::Single_SC_to_NC(win_h, info.width);

        CommandQueue.push_back(cmd);

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
            if(cmd.type == MeshType::TRIANGLE) {

                // Conversion
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
                    (unsigned int)( (IB_offset - 1) + 1 ),
                    (unsigned int)( (IB_offset - 1) + 2 ),
                    (unsigned int)( (IB_offset - 1) + 3 )
                };

                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, IB_offset*sizeof(float), sizeof(index_data), index_data);
                IB_offset += 3;
            }

            if(cmd.type == MeshType::RECTANGLE)
            {
                float vert_data[6*4] = {
                    cmd.pos.x, cmd.pos.y, cmd.pos.z,
                    cmd.color.r, cmd.color.g, cmd.color.b,

                    cmd.pos.x, cmd.pos.y-cmd.h, cmd.pos.z,
                    cmd.color.r, cmd.color.g, cmd.color.b,

                    cmd.pos.x+cmd.w , cmd.pos.y-cmd.h , cmd.pos.z,
                    cmd.color.r, cmd.color.g, cmd.color.b,

                    cmd.pos.x+cmd.w , cmd.pos.y, cmd.pos.z,
                    cmd.color.r, cmd.color.g, cmd.color.b
                };

                glBufferSubData(GL_ARRAY_BUFFER, VB_offset*sizeof(float), sizeof(vert_data), vert_data);
                VB_offset += 24;

                unsigned int index_data[6] = {
                    (unsigned int)( (IB_offset - 1) + 1 ),
                    (unsigned int)( (IB_offset - 1) + 2 ),
                    (unsigned int)( (IB_offset - 1) + 3 ),
                    (unsigned int)( (IB_offset - 1) + 4 ),
                    (unsigned int)( (IB_offset - 1) + 1 ),
                    (unsigned int)( (IB_offset - 1) + 3 )
                };

                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, IB_offset*sizeof(unsigned int), sizeof(index_data), index_data);
                IB_offset += 6;
            }
        }
        glUseProgram(gl_shader_program_id);
        glBindVertexArray(gl_global_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_global_IB);

        // glm::mat4 projection = glm::perspective(
        //     glm::radians(45.0f),
        //     (float)win_w / win_h, 
        //     0.1f, 
        //     100.0f
        // );

        // glm::mat4 view = glm::lookAt(
        //     glm::vec3({ 0.0f, 0.0f, -3.0f }), 
        //     glm::vec3({ 0.0f, 0.0f, 0.0f } ), 
        //     glm::vec3({ 0.0f, 1.0f, 0.0f } )
        // );

        // glm::mat4 VP = projection * view;

        glm::mat4 VP = _renderer_cam->GetVP();

        // Uniforms
        glUniform1f(gl_Uniforms["Shader_uAspectFix_X"], aspect_ratio);
        glUniformMatrix4fv(gl_Uniforms["VP"], 1, GL_FALSE, &VP[0][0]);

        // Drawing 
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

        //sleep_ms(10); 
    }
    
    bool Renderer::ShouldEndLoop()
    {
        return glfwWindowShouldClose(s_Window);
    }


    void Renderer::Shutdown() {

        if(DefaultCamera) delete _renderer_cam;

        igRender.Shutdown();

        glfwDestroyWindow(s_Window);
        glfwTerminate();
        SF_CORE_INFO_("Renderer shutdown!!!", "Renderer");
    }
}