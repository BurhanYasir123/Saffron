#pragma once

#include <iostream>

// Define ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define SF_CORE_INFO(x) std::cout << BLUE   << "[Saffron]--[Info]:  " << x << RESET << '\n';
#define SF_CORE_WARN(x) std::cout << YELLOW << "[Saffron]--[Warn]:  " << x << RESET << '\n';
#define SF_CORE_ERR(x)  std::cout << RED    << "[Saffron]--[Error]: " << x << RESET << '\n';

#define SF_CORE_INFO_(x, y) std::cout << BLUE   << "[Saffron::" << y << "]--[Info]:  " << x << RESET << '\n';
#define SF_CORE_WARN_(x, y) std::cout << YELLOW << "[Saffron::" << y << "]--[Warn]:  " << x << RESET << '\n';
#define SF_CORE_ERR_(x, y)  std::cout << RED    << "[Saffron::" << y << "]--[Error]: " << x << RESET << '\n';

#define SF_INFO(x) std::cout << CYAN   << "[Saffron::Application]--[Info]:  " << x << RESET << '\n';
#define SF_WARN(x) std::cout << YELLOW << "[Saffron::Application]--[Warn]:  " << x << RESET << '\n';
#define SF_ERR(x)  std::cout << RED    << "[Saffron::Application]--[Error]: " << x << RESET << '\n';