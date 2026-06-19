#include "Core.h"
#include "Renderer/Renderer.h"
#include "Saffron.h"
#include <GL/gl.h>
#include <vector>

class Sandbox : public Saffron::Application {
public:
	int framei;

	Sandbox() {
		framei = 0;
	}
	~Sandbox() {}

	void Run()
	{
		SF_INFO("HIIIIIIIIIIIIIIIIIIIIIII");

		Saffron::RendererInitInfo info{};
		info.window_width = 800;
		info.window_height = 600;
		info.window_title = "Saffron";

		Saffron::Renderer r(info);

		Saffron::EventEngine ev(r);

		SF_INFO("Init Done!!!")

		std::vector<Saffron::TriangleInfo> objs;

		while (!r.ShouldEndLoop()) {
		    r.BeginFrame();

    		framei += 1;

		    if(ev.IsKeyDown(Saffron::Key::D0)){ r.SetBackgroundColor({0.1f, 0.3f, 0.4f}); }
		    else{ r.SetBackgroundColor({0.1f, 0.9f, 0.4f}); }

		    ImGuiIO& io = ImGui::GetIO();

		    // --- ImGui Window for Triangle Creation ---

		    static float pos[3] = {0.0f, 0.0f, 0.0f};
    		static float color[3] = { 0.4f, 0.7f, 0.2f };
    		static float size = 0.5f;
		
    		ImGui::Begin("Triangle Creator");
		
    		ImGui::Text("Set Vertex Positions:");
    		ImGui::SliderFloat("X:", &pos[0], -1.0f, 1.0f);
    		ImGui::SliderFloat("Y:", &pos[1], -1.0f, 1.0f);
    		ImGui::SliderFloat("Z:", &pos[2], -1.0f, 1.0f);
    		ImGui::Text("Size");
    		ImGui::SliderFloat("::", &size, 0.0f, 2.0f);
		
    		ImGui::ColorEdit3("Color", color);

    		if(ImGui::Button("Add Triangle")) {
    		    Saffron::TriangleInfo info;
    		    info.pos = { pos[0], pos[1], pos[2] };
    		    info.size = size;
    		    info.color = { color[0], color[1], color[2] };
    		    objs.push_back(info);
    		}
		
    		ImGui::End();


    		float fps;

		    if((framei%10) == 0){ fps = 1.0f / io.DeltaTime; };

    		ImGui::Begin("Demo");
    		ImGui::Text("FPS: %.1f", fps);
    		// if(ImGui::Button("Do THings")) {
    		// }
    		ImGui::End();    	

			for(int i=0;i!=10;i++)
	    	{
	    		Saffron::TriangleInfo info;
	    		info.pos = { (i/10.0f)-0.5f, 0.5f, 0.0f };
	    		info.size = 0.5f;
	    		info.color = {(i*10.0f)/100.0f, (i*10)/100.0f, (i*10.0f)/100.0f};
	    		r.DrawTriangle(info);
	    	}

	    	for(auto obj : objs)
	    	{
	    		r.DrawTriangle(obj);
	    	}

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