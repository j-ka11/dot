#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object/ArObject.h"

namespace dotGLASS {
	namespace Object {

		class Lamp : public ArObject {
		public:
			Lamp();
			~Lamp();

			void bind();
			void unBind();
			void draw();

			inline glm::vec3 getLightPosition() const { return lightPosition; }
		private:
			GPU::IndexBuffer* indexBuffer;
			glm::vec3 lightPosition;
			unsigned int vertexArrayID;
			GPU::VertexBuffer* vertexBuffer;
		};

	}
}
