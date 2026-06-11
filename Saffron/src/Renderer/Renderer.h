#pragma once

#include "Core.h"
#include "ImGuiRenderer.h"


namespace Saffron
{
	enum class RenderCommand
	{
		NULL_COMMAND, SCREEN_CLEAR, TRIANGLE
	};

	struct RenderInfo
	{
		RenderInfo() {};

		RenderCommand command;
		glm::vec3 color;


		bool operator==(const RenderInfo& other) const {
            return command == other.command &&
                   glm::all(glm::equal(color, other.color));
            //return true;
        }
	};

	struct RendererInitInfo
	{
		RendererInitInfo() {};
		int window_height;
		int window_width;
		const char* window_title;
	};


	class Renderer
	{
	private:
		bool isInitialized = false;
	public:
		Renderer(RendererInitInfo info);
		~Renderer();

		ImGuiRenderer igRender;
		std::vector<RenderInfo> RenderQueue;

		GLFWwindow* GetWindowHandle();
		bool IsInitialized() { return isInitialized; };
		void Init(RendererInitInfo info);
		void SetBackgroundColor(glm::vec3 color);
		void BeginFrame();
		void EndFrame();
		bool ShouldEndLoop();
		void Shutdown();
	};
}