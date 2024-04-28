#pragma once

#include <iostream>

#include "GL/glew.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearError();\
	x;\
	ASSERT(glLogError(#x, __FILE__, __LINE__))

void glClearError();
bool glLogError(const char* function, const char* file, int line);

class ErrorDirectives {
};

