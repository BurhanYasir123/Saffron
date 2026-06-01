#pragma once

#include <iostream>

#define SF_INFO(x) std::cout << "[Saffron::AppInfo]:  " << x << '\n';
#define SF_WARN(x) std::cout << "[Saffron::AppWarn]:  " << x << '\n';
#define SF_ERR(x)  std::cout << "[Saffron::AppError]: " << x << '\n';

#define SF_CORE_INFO(x) std::cout << "[Saffron::SystemInfo]:  " << x << '\n';
#define SF_CORE_WARN(x) std::cout << "[Saffron::SystemWarn]:  " << x << '\n';
#define SF_CORE_ERR(x)  std::cout << "[Saffron::SystemError]: " << x << '\n';