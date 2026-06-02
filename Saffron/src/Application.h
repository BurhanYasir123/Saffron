#pragma once

#include "Core.h"

namespace Saffron
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};

	Application* CreateApplication();
}