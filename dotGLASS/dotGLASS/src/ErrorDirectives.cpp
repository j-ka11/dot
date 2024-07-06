#include "ErrorDirectives.h"

void dotGLASS::glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool dotGLASS::glLogError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL Error: " << error << std::endl;
		std::cout << "Function name: " << function << std::endl;
		std::cout << "File name: " << file << std::endl;
		std::cout << "Line number: " << line << std::endl << std::endl;
		return false;
	}
	return true;
}
