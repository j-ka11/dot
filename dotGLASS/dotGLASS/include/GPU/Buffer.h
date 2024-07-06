#pragma once

#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"

#include "ErrorDirectives.h"
#include "Vertex.h"

namespace dotGLASS {
	namespace GPU {

		class Buffer {
			public:
				Buffer();
				Buffer(const void* vertices, unsigned int size);
				Buffer(std::vector<Vertex> vertices);
				Buffer(unsigned int* indices, unsigned int count);
				Buffer(std::vector<unsigned int> indices);
				~Buffer();

				virtual void bind() const;
				virtual void unBind() const;
			protected:
				unsigned int bufferID;
		};

	}
}
