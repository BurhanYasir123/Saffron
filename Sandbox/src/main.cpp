#include "Saffron.h"

class Sandbox : public Saffron::Application {
public:
	Sandbox() {}
	~Sandbox() {}

	int frame_num;

	void Run()
	{
		SF_INFO("HIIIIIIIIIIIIIIIIIIIIIII");

		frame_num++;

		Saffron::RendererInitInfo info{};

		info.window_width = 800;
		info.window_height = 600;
		info.window_title = "Saffron";

		Saffron::Renderer r(info);

		Saffron::EventEngine ev(r);

		SF_INFO("Init Done!!!")

		for(int i=0;i!=10;i++)
	    {
	    	Saffron::TriangleInfo info;
	    	info.point1 = Saffron::Vertex({ (i/10.0f)-1.0f, -0.5f, 0.0f});
	    	info.point2 = Saffron::Vertex({ (i/10.0f), -0.5f, 0.0f});
	    	info.point3 = Saffron::Vertex({ (i/10.0f)-0.5f,  0.5f, 0.0f});
	    	info.color = {(i*10.0f)/100.0f, (i*10)/100.0f, (i*10.0f)/100.0f};
	    	r.InitTriangle(info);
	    }

		while (!r.ShouldEndLoop()) {
		    r.BeginFrame();

		    if(ev.IsKeyDown(Saffron::Key::D0)){ r.SetBackgroundColor({0.1f, 0.3f, 0.4f}); }
		    else{ r.SetBackgroundColor({0.1f, 0.9f, 0.4f}); }

		    glfwPollEvents();

		    ImGuiIO& io = ImGui::GetIO();

		    if(frame_num == 1 || (frame_num%100) == 0) auto fps = 1.0f / io.DeltaTime;

    		ImGui::Begin("Demo");
    		ImGui::Text("FPS: %.1f", 1.0f / io.DeltaTime);
    		ImGui::End();

		    r.EndFrame();
		}

	}
};

namespace Saffron
{
	Application* CreateApplication() {
		return new Sandbox();
	}
}