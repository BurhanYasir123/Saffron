#include "ImGuiRenderer.h"

namespace Saffron
{
	ImGuiRenderer::ImGuiRenderer(ImGuiInitInfo info)
	{
		Init(info);
	}

	ImGuiRenderer::~ImGuiRenderer()
	{
		
	}

	void ImGuiRenderer::Init(ImGuiInitInfo info)
	{
		IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(info.window, true);
        ImGui_ImplOpenGL3_Init(info.glsl_version);

        SF_CORE_INFO_("ImGui " << IMGUI_VERSION << " inttialized with OpenGL", "ImGuiRenderer");
        isInitialized = true;
	}

	void ImGuiRenderer::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();   
	}

	void ImGuiRenderer::EndFrame()
	{
		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());    
	}

	void ImGuiRenderer::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        SF_CORE_INFO_("ImGuiRenderer Shutdown!!!", "ImGuiRenderer")
	}
}