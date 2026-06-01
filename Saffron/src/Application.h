#pragma once

#include "Core.h"

namespace Saffron
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}