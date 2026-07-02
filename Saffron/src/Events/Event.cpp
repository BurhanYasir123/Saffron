#include "Event.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>

namespace Saffron
{
	EventEngine::EventEngine(Renderer* renderer)
		: io(ImGui::GetIO())
	{
		_r = renderer;
		if(!renderer->IsInitialized())
		{	
			SF_CORE_ERR_("ImGuiRenderer not intialized!!!", "Event");
		}
	}

	EventEngine::~EventEngine()
	{

	}

	bool EventEngine::IsKeyDown(int key)
	{
		return glfwGetKey(_r->GetWindowHandle(), key) == GLFW_PRESS;
	}

	bool EventEngine::IsKeyPressed(int key)
	{
		return glfwGetKey(_r->GetWindowHandle(), key) == GLFW_PRESS;
	}
	
	bool EventEngine::IsKeyReleased(int key)
	{
		return glfwGetKey(_r->GetWindowHandle(), key) == GLFW_RELEASE;
	}

	bool EventEngine::IsMouseDown(int button)
	{
		return glfwGetMouseButton(_r->GetWindowHandle(), button ) == GLFW_PRESS;
	}

	bool EventEngine::IsMouseClicked(int button)
	{
		return glfwGetMouseButton(_r->GetWindowHandle(), button ) == GLFW_PRESS;
	}

	bool EventEngine::IsMouseReleased(int button)
	{
		return glfwGetMouseButton(_r->GetWindowHandle(), button ) == GLFW_RELEASE;
	}

	float EventEngine::GetMouseWheel()
	{
		return io.MouseWheel;
	}

	glm::vec2 EventEngine::GetMousePos()
	{
		double x; double y; 
		glfwGetCursorPos(_r->GetWindowHandle(), &x, &y);
		return glm::vec2(x-(_r->GetWindowSize().x/2), y-(_r->GetWindowSize().y/2));
	}

}