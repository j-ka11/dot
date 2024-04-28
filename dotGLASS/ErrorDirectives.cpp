#include "ErrorDirectives.h"

using namespace std;
void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool glLogError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		cout << "OpenGL Error: " << error << endl;
		cout << "Function name: " << function << endl;
		cout << "File name: " << file << endl;
		cout << "Line number: " << line << endl << endl;
		return false;
	}
	return true;
}