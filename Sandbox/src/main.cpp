#include "Saffron.h"
#include <iostream>

class Sandbox : public Saffron::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

namespace Saffron
{
	Application* CreateApplication() {
		return new Sandbox();
	}
}