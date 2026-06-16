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
	    	info.pos = { i/10.0f, 0.5f, 0.5f };
	    	info.size = 0.5f;
	    	info.color = {(i*10.0f)/100.0f, (i*10)/100.0f, (i*10.0f)/100.0f};
	    	r.InitTriangle(info);
	    }

	    Saffron::TriangleInfo tinfo;

	    tinfo.color = { 0.1f, 0.2, 0.5f };
	    int tid = r.InitTriangle(tinfo);

		while (!r.ShouldEndLoop()) {
		    r.BeginFrame();

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
			
			unsigned int id;

    		if(ImGui::Button("Add Triangle")) {
    		    Saffron::TriangleInfo info;
    		    info.pos = { pos[0], pos[1], pos[2] };
    		    info.size = size;
    		    info.color = { color[0], color[1], color[2] };
    		    id = r.InitTriangle(info);
    		}
		
    		ImGui::End();


		    if(frame_num == 1 || (frame_num%100) == 0) auto fps = 1.0f / io.DeltaTime;

    		ImGui::Begin("Demo");
    		ImGui::Text("FPS: %.1f", 1.0f / io.DeltaTime);
    		ImGui::Text("%.1f", (float)tid);
    		if(ImGui::Button("Do THings")) {
    			// std::vector<float> vert = {
    			// 	r.collectedVerts[(tid*18)+0 ], r.collectedVerts[(tid*18)+1 ], r.collectedVerts[(tid*18)+2 ], 
    			// 	r.collectedVerts[(tid*18)+3 ], r.collectedVerts[(tid*18)+4 ], r.collectedVerts[(tid*18)+5 ], 
    			// 	r.collectedVerts[(tid*18)+6 ], r.collectedVerts[(tid*18)+7 ], r.collectedVerts[(tid*18)+8 ], 
    			// 	r.collectedVerts[(tid*18)+9 ], r.collectedVerts[(tid*18)+10], 1.0f, //collectedVerts[(tid*18)+11], 
    			// 	r.collectedVerts[(tid*18)+12], r.collectedVerts[(tid*18)+13], r.collectedVerts[(tid*18)+14],
    			// 	r.collectedVerts[(tid*18)+15], r.collectedVerts[(tid*18)+16], r.collectedVerts[(tid*18)+17]
    			// };
    			// glBufferSubData(GL_ARRAY_BUFFER, (tid*18)*sizeof(float), vert.size()*sizeof(float), vert.data());
    			auto info = r.GetTriangleByIndex(id);
    			info.color = { 1.0f, 0.0f, 0.0f };
    			r.EditTriangle(id, info);
    		}
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