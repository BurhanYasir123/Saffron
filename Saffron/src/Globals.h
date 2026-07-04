#pragma once

namespace Runtime
{
	namespace RenderAPI
	{
		static const char* API_Name = "OpenGL";
		static const bool ImGuiSupport = true;
		static const bool TexturesSupport = true;
	}

    const size_t MAX_VERTS = 10000; 
    const size_t MAX_INDICES = 20000;
}	