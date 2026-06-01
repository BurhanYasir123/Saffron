#pragma once

#include "Core.h"
#include "Application.h"

extern Saffron::Application* Saffron::CreateApplication();

int main(int argc, char** argv) {
	auto app = Saffron::CreateApplication();
	app->Run();
	delete app;
	SF_CORE_INFO("App Exited!!!");
	return 0;
}