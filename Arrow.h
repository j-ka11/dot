#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "ArObject.h"

class Arrow : public ArObject {
public:
	Arrow();
	~Arrow();
};
