#pragma once

#include "Core.h"

namespace Saffron
{

	struct ImGuiInitInfo
	{
		ImGuiInitInfo() {};
		GLFWwindow* window;
		const char* glsl_version;
	};

	class ImGuiRenderer
	{
	public:
		ImGuiRenderer() {};
		ImGuiRenderer(ImGuiInitInfo info);
		~ImGuiRenderer();

		void Init(ImGuiInitInfo info);
		void BeginFrame();
		void EndFrame();
		void Shutdown();
	};
}
