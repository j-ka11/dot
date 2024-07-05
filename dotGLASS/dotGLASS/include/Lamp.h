#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ArObject.h"

class Lamp : public ArObject {
	public:
		Lamp();
		~Lamp();

		void bind();
		void unBind();
		void draw();

		inline glm::vec3 getLightPosition() const { return lightPosition; }
	private:
		unsigned int m_VertexArrayID;

		glm::vec3 lightPosition;

		IndexBuffer* indexBuffer;
		VertexBuffer* vertexBuffer;
};
