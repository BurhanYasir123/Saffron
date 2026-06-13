#pragma once

#include "Core.h"
#include "ImGuiRenderer.h"
#include "Shaders.h"

namespace Saffron
{

	struct Vertex
	{
		Vertex() {}
		Vertex(glm::vec3 _pos) {
			pos = _pos;
		} 

		glm::vec3 pos;
		glm::vec3 color;
	};

	struct TriangleInfo
	{
		TriangleInfo() {}

		Vertex point1;
		Vertex point2;
		Vertex point3;
		glm::vec3 color;
	};

	enum class RenderCommand
	{
		NULL_COMMAND, SCREEN_CLEAR, TRIANGLE
	};

	struct RenderInfo
	{
		RenderInfo() {};

		RenderCommand command;
		glm::vec3 color;
		std::vector<Vertex> verts;

		unsigned int VB;

	// 	bool operator==(const RenderInfo& other) const {
            // return command == other.command &&
            //        glm::all(glm::equal(color, other.color));
            // //return true;
        //}
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
		unsigned int gl_shader_program_id;
		unsigned int gl_global_VAO;
		unsigned int gl_global_VB;
	public:
		Renderer(RendererInitInfo info);
		~Renderer();

		ImGuiRenderer igRender;
		std::vector<RenderInfo> RenderQueue;

		GLFWwindow* GetWindowHandle();
		bool IsInitialized() { return isInitialized; };
		void Init(RendererInitInfo info);
		void SetBackgroundColor(glm::vec3 color);
		void DrawTriangle(TriangleInfo info);
		void BeginFrame();
		void EndFrame();
		bool ShouldEndLoop();
		void Shutdown();
	};
}