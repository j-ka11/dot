#pragma once

#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"

#include "VertexArray.h"
#include "ArObject.h"
#include "ErrorDirectives.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void draw(const VertexArray* va, const IndexBuffer* ib) const;
	void draw(ArObject* arObject);
	void clear() const;
};
