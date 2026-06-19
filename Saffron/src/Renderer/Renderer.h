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

		glm::vec3 pos;
		float size;
		glm::vec3 color;
	};

	struct RectangleInfo
	{
		RectangleInfo() {}

		glm::vec3 pos;
		float width;
		float height;
		glm::vec3 color;
	};

	struct RendererInitInfo
	{
		RendererInitInfo() {};
		int window_height;
		int window_width;
		const char* window_title;
	};

	enum class MeshType
	{
		TRIANGLE, RECTANGLE, NULL_COMMAND
	};

	struct RenderCommand
	{	
		RenderCommand() {}
		MeshType type;
		glm::vec3 pos;
		glm::vec3 color;
		float size;
		float w;
		float h;
	};

	class Renderer
	{
	private:
		bool isInitialized = false;
		unsigned int gl_shader_program_id;
		unsigned int gl_global_VAO;
		unsigned int gl_global_VB;
		unsigned int gl_global_IB;
		int VB_offset;
		int IB_offset;
	public:
		Renderer(RendererInitInfo info);
		~Renderer();

		ImGuiRenderer igRender;
		std::vector<RenderCommand> CommandQueue;

		std::vector<float> collectedVerts;
		std::vector<unsigned int> collectedIndicies;


		GLFWwindow* GetWindowHandle();
		bool IsInitialized() { return isInitialized; };
		void Init(RendererInitInfo info);
		void SetBackgroundColor(glm::vec3 color);
		int DrawTriangle(TriangleInfo info);
		int DrawRectangle(RectangleInfo info);
		void BeginFrame();
		void EndFrame();
		bool ShouldEndLoop();
		void Shutdown();
	};
}