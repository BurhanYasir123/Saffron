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


	class Renderer
	{
	public:
		Renderer(const char* window_title, int window_width, int window_height);
		~Renderer();

		ImGuiRenderer igRender;
		std::vector<RenderInfo> RenderQueue;
		std::vector<RenderInfo> LastRenderQueue;

		GLFWwindow* GetWindowHandle();
		void Init(const char* window_title, int window_width, int window_height);
		void SetBackgroundColor(glm::vec3 color);
		void BeginFrame();
		void EndFrame();
		bool ShouldEndLoop();
		void Shutdown();
	};
}