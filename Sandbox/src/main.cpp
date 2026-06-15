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

		    ImGuiIO& io = ImGui::GetIO();

		    // --- ImGui Window for Triangle Creation ---
    		static float p1[3] = { -0.5f, -0.5f, 0.0f };
    		static float p2[3] = {  0.5f, -0.5f, 0.0f };
    		static float p3[3] = {  0.0f,  0.5f, 0.0f };
    		static float color[3] = { 0.4f, 0.7f, 0.2f };
		
    		ImGui::Begin("Triangle Creator");
		
    		ImGui::Text("Set Vertex Positions:");
    		ImGui::SliderFloat3("Point 1", p1, -1.0f, 1.0f);
    		ImGui::SliderFloat3("Point 2", p2, -1.0f, 1.0f);
    		ImGui::SliderFloat3("Point 3", p3, -1.0f, 1.0f);
		
    		ImGui::ColorEdit3("Color", color);
		
    		if(ImGui::Button("Add Triangle")) {
    		    Saffron::TriangleInfo info;
    		    info.point1 = Saffron::Vertex({ p1[0], p1[1], p1[2] });
    		    info.point2 = Saffron::Vertex({ p2[0], p2[1], p2[2] });
    		    info.point3 = Saffron::Vertex({ p3[0], p3[1], p3[2] });
    		    info.color = { color[0], color[1], color[2] };
    		    r.InitTriangle(info);
    		}
		
    		ImGui::End();


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