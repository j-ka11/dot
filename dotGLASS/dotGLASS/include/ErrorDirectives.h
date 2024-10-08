#pragma once

#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"

namespace dotGLASS {

	#define ASSERT(x) if (!(x)) __debugbreak();
	#define GLCall(x) glClearError();\
		x;\
		ASSERT(glLogError(#x, __FILE__, __LINE__))

	void glClearError();
	bool glLogError(const char* function, const char* file, int line);

	class ErrorDirectives {};

}
