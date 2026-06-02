#include "Saffron.h"
#include <iostream>

class Sandbox : public Saffron::Application {
public:
	Sandbox() {}
	~Sandbox() {}

	int frame_num;

	void Run()
	{
		SF_INFO("HIIIIIIIIIIIIIIIIIIIIIII");

		frame_num++;
		Saffron::Renderer r("Saffron", 800, 600);
		auto window = r.GetWindowHandle();

		while (!r.ShouldEndLoop()) {
		    r.BeginFrame();

		    r.SetBackgroundColor({0.1f, 0.3f, 0.4f});

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