#pragma once

#include "Core.h"

namespace Saffron
{
	class Renderer
	{
	public:
		Renderer(const char* window_title, int window_width, int window_height);
		~Renderer();

		GLFWwindow* GetWindowHandle();
		void Init(const char* window_title, int window_width, int window_height);
		void SetBackgroundColor(glm::vec3 color);
		void BeginFrame();
		void EndFrame();
		bool ShouldEndLoop();
		void Shutdown();
	};
}