#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "ArObject.h"

using namespace std;
class Nanosuit : public ArObject {
public:
	Nanosuit();
	~Nanosuit();
};
