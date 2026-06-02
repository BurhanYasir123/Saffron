#pragma once

#include "Core.h"
#include "Application.h"

extern Saffron::Application* Saffron::CreateApplication();

int main(int argc, char** argv) {
	SF_CORE_INFO_("This is a Information Log.", "Log");
	SF_CORE_WARN_("This is a Warning Log.", "Log");
	SF_CORE_ERR_( "This is a Error Log.", "Log"); 
	std::cout << '\n';

	auto app = Saffron::CreateApplication();
	app->Run();
	delete app;
	SF_CORE_INFO("App Exited!!!");
	return 0;
}