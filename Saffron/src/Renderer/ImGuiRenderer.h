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
	private:
		bool isInitialized = false;
	public:
		ImGuiRenderer() {};
		ImGuiRenderer(ImGuiInitInfo info);
		~ImGuiRenderer();

		bool IsInitialized() { return isInitialized; }
		void Init(ImGuiInitInfo info);
		void BeginFrame();
		void EndFrame();
		void Shutdown();
	};
}
