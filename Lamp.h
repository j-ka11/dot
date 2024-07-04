#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ArObject.h"
#include "VertexArray.h"

class Lamp : public ArObject {
	public:
		Lamp();
		~Lamp();

		void bind();
		void unBind();
		void draw();

		inline glm::vec3 getLightPosition() const { return lightPosition; }
	private:
		glm::vec3 lightPosition;

		IndexBuffer* indexBuffer;
		VertexArray* vertexArray;
		VertexBuffer* vertexBuffer;
};
