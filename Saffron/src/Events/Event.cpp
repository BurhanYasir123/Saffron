#include "Event.h"

namespace Saffron
{
	EventEngine::EventEngine(Renderer& renderer)
		: io(ImGui::GetIO())
	{
		if(!renderer.IsInitialized())
		{	
			SF_CORE_ERR_("ImGuiRenderer not intialized!!!", "Event");
		}
	}

	EventEngine::~EventEngine()
	{

	}

	bool EventEngine::IsKeyDown(ImGuiKey key)
	{
		return ImGui::IsKeyDown((key));
	}

	bool EventEngine::IsKeyPressed(ImGuiKey key)
	{
		return ImGui::IsKeyPressed((key));
	}
	
	bool EventEngine::IsKeyReleased(ImGuiKey key)
	{
		return ImGui::IsKeyReleased((key));
	}

	bool EventEngine::IsMouseDown(int button)
	{
		if(boundsCheckMouse(button))
		{
			io.MouseDown[button];
		}
		return false;
	}

	bool EventEngine::IsMouseClicked(int button)
	{
		return ImGui::IsMouseClicked(button);
	}

	bool EventEngine::IsMouseReleased(int button)
	{
		return ImGui::IsMouseReleased(button);
	}

	float EventEngine::GetMouseWheel()
	{
		return io.MouseWheel;
	}

	glm::vec2 EventEngine::GetMousePos()
	{
		return glm::vec2(io.MousePos.x, io.MousePos.y);
	}

}