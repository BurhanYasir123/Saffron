#pragma once

#include "Core.h"
#include "Renderer/Renderer.h"

enum class SaffronKey
{
    None = 0,
    A,
    B,
    C,
    D,
    W,
    S,
    Space,
    Enter,
    Escape,
    Left,
    Right,
    Up,
    Down,
};

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

		inline ImGuiKey ToImGuiKey(SaffronKey key)
		{
		    switch (key)
		    {
		        case SaffronKey::A:      return ImGuiKey_A;
		        case SaffronKey::B:      return ImGuiKey_B;
		        case SaffronKey::C:      return ImGuiKey_C;
		        case SaffronKey::D:      return ImGuiKey_D;
		        case SaffronKey::W:      return ImGuiKey_W;
		        case SaffronKey::S:      return ImGuiKey_S;
		        case SaffronKey::Space:  return ImGuiKey_Space;
		        case SaffronKey::Enter:  return ImGuiKey_Enter;
		        case SaffronKey::Escape: return ImGuiKey_Escape;
		        case SaffronKey::Left:   return ImGuiKey_LeftArrow;
		        case SaffronKey::Right:  return ImGuiKey_RightArrow;
		        case SaffronKey::Up:     return ImGuiKey_UpArrow;
		        case SaffronKey::Down:   return ImGuiKey_DownArrow;
		        default:                           return ImGuiKey_None;
		    }
		}

	public:
		EventEngine(Renderer& renderer);
		~EventEngine();

		bool IsKeyDown(SaffronKey key);
		bool IsKeyPressed(SaffronKey key);
		bool IsKeyReleased(SaffronKey key);
		bool IsMouseDown(int button);
		bool IsMouseClicked(int button);
		bool IsMouseReleased(int button);
		float GetMouseWheel();
		glm::vec2 GetMousePos();
	};
}