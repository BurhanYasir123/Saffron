#include "Core.h"
#include "Events/keys.h"
#include "Log.h"
#include "Renderer/Camera.h"
#include "Renderer/Renderer.h"
#include "Saffron.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
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

		Saffron::Camera cam;

		Saffron::CameraConfigInfo caminfo;
		caminfo.FOV = 45;
		caminfo.pos = { 0.0f, 0.0f, -2.0f };
		caminfo.window_width = 800;
		caminfo.window_height = 600;

		cam.ConfigCamera(caminfo);

		r.RegisterCamera(&cam);

		Saffron::EventEngine ev(&r);

		SF_INFO("Init Done!!!")

		std::vector<Saffron::TriangleInfo> objs;

		Saffron::TriangleInfo trinfo;
	    	trinfo.pos = { 0, 0, 0 };
	    	trinfo.size = 100;
	    	trinfo.color = { 1.0f, 0.0f, 0.5f };

	    float fps;

		while (!r.ShouldEndLoop()) {
		    r.BeginFrame();

    		framei += 1;

		    if(ev.GetMousePos().x < 100){ r.SetBackgroundColor({0.1f, 0.3f, 0.4f}); }
		    else{ r.SetBackgroundColor({0.1f, 0.9f, 0.4f}); }

		    // Camera
		    if(ev.IsKeyDown(Saffron::Key::W)){
		    	caminfo.pos.z += 0.01f;
		    	cam.OverrideCameraPos(caminfo.pos);
		    } if (ev.IsKeyDown(Saffron::Key::A)){
		    	caminfo.pos.x += 0.01f;
		    	cam.OverrideCameraPos(caminfo.pos);
		    } if (ev.IsKeyDown(Saffron::Key::S)){
		    	caminfo.pos.z -= 0.01f;
		    	cam.OverrideCameraPos(caminfo.pos);
		    } if (ev.IsKeyDown(Saffron::Key::D)){
		    	caminfo.pos.x -= 0.01f;
		    	cam.OverrideCameraPos(caminfo.pos);
		    } if (ev.IsKeyDown(Saffron::Key::E)){
		    	caminfo.pos.y -= 0.01f;
		    	cam.OverrideCameraPos(caminfo.pos);
		    } if (ev.IsKeyDown(Saffron::Key::Q)){
		    	caminfo.pos.y += 0.01f;
		    	cam.OverrideCameraPos(caminfo.pos);
		    } 

		    ImGuiIO& io = ImGui::GetIO();

		    // if( glfwGetKey(r.GetWindowHandle(), GLFW_KEY_ENTER) == GLFW_PRESS )
		    // {
		    // 	r.SetBackgroundColor({0.0f, 0.0f, 0.0f});
		    // }

		    // --- ImGui Window for Triangle Creation ---

		    static float pos[3] = {0.0f, 0.0f, 0.0f};
    		static float color[3] = { 0.4f, 0.7f, 0.2f };
    		static float size = 100;
		
    		ImGui::Begin("Triangle Creator");
		
    		ImGui::Text("Set Vertex Positions:");
    		ImGui::SliderFloat("X:", &pos[0], -400, 400);
    		ImGui::SliderFloat("Y:", &pos[1], -300, 300);
    		ImGui::SliderFloat("Z:", &pos[2], -10, 10);
    		ImGui::Text("Size");
    		ImGui::SliderFloat("::", &size, 0, 200);
		
    		ImGui::ColorEdit3("Color", color);

    		if(ImGui::Button("Add Triangle")) {
    		    Saffron::TriangleInfo info;
    		    info.pos = { pos[0], pos[1], pos[2] };
    		    info.size = size;
    		    info.color = { color[0], color[1], color[2] };
    		    objs.push_back(info);
    		}
		
    		ImGui::End();

		    if((framei%10) == 0){ fps = 1.0f / io.DeltaTime; };

    		ImGui::Begin("Demo");
    		ImGui::Text("FPS: %.1f", fps);
    		// if(ImGui::Button("Do THings")) {
    		// }
    		ImGui::End();    	

			for(int i=0;i!=10;i++)
	    	{
	    		Saffron::TriangleInfo info;
	    		info.pos = { (i*40)-200, 150, 0 };
	    		info.size = 150;
	    		info.color = {(i*10.0f)/100.0f, (i*10)/100.0f, (i*10.0f)/100.0f};
	    		r.DrawTriangle(info);
	    	}

	    	// Triangle
	    	// if(ev.IsKeyDown(Saffron::Key::W)) { trinfo.pos.y += 0.5; }
			// if(ev.IsKeyDown(Saffron::Key::A)) { trinfo.pos.x += 0.5; }
			// if(ev.IsKeyDown(Saffron::Key::S)) { trinfo.pos.y -= 0.5; }
			// if(ev.IsKeyDown(Saffron::Key::D)) { trinfo.pos.x -= 0.5; }

	    	r.DrawTriangle(trinfo);


	    	Saffron::RectangleInfo rectiinfo;
	    	rectiinfo.pos = { 0, 0, 0 };
	    	rectiinfo.height = 150;
	    	rectiinfo.width = 150;
	    	rectiinfo.color = { 0.3f, 0.4f, 0.7f };

	    	r.DrawRectangle(rectiinfo);

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