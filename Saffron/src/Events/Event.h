#pragma once

#include "Core.h"
#include "Renderer/Renderer.h"
#include "keys.h"


namespace Saffron
{
	class EventEngine
	{
	private:
		ImGuiIO& io;

		bool boundsCheckMouse(int key)
		{
			if (key < 0 || key >= IM_ARRAYSIZE(io.MouseDown)) {
        		return false;
    		} 
    		return true;
		}

	public:
		EventEngine(Renderer& renderer);
		~EventEngine();

		bool IsKeyDown(ImGuiKey key);
		bool IsKeyPressed(ImGuiKey key);
		bool IsKeyReleased(ImGuiKey key);
		bool IsMouseDown(int button);
		bool IsMouseClicked(int button);
		bool IsMouseReleased(int button);
		float GetMouseWheel();
		glm::vec2 GetMousePos();
	};
}