#pragma once

#include "Core.h"
#include "Renderer/Renderer.h"
#include "imgui.h"
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

		Renderer* _r;

	public:
		EventEngine(Renderer* renderer);
		~EventEngine();

		bool IsKeyDown(int key);
		bool IsKeyPressed(int key);
		bool IsKeyReleased(int key);
		bool IsMouseDown(int button);
		bool IsMouseClicked(int button);
		bool IsMouseReleased(int button);
		float GetMouseWheel();
		glm::vec2 GetMousePos();
	};
}