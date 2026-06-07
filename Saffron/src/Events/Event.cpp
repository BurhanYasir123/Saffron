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

	bool EventEngine::IsKeyDown(SaffronKey key)
	{
		return ImGui::IsKeyDown(ToImGuiKey(key));
	}

	bool EventEngine::IsKeyPressed(SaffronKey key)
	{
		return ImGui::IsKeyPressed(ToImGuiKey(key));
	}
	
	bool EventEngine::IsKeyReleased(SaffronKey key)
	{
		return ImGui::IsKeyReleased(ToImGuiKey(key));
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