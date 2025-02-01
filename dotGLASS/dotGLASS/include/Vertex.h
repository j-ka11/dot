/**
 * @file Vertex.h
 */

#pragma once

#include <glm/glm.hpp>

namespace dotGLASS {

	/**
	 * @class Vertex Vertex.h "Vertex.h"
	 */
	class Vertex {
		public:
			glm::vec3 positions;
			glm::vec3 normals;
			glm::vec2 texCoords;
	};

}
