#pragma once

#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"

#include "GPU/Buffer.h"

namespace dotGLASS {
	namespace GPU {

		class IndexBuffer : public Buffer {
			public:
				IndexBuffer(unsigned int* indices, unsigned int count);
				IndexBuffer(std::vector<unsigned int> indices);
				~IndexBuffer();

				void bind() const;
				void unBind() const;

				inline unsigned int getCount() const { return count; }
			private:
				unsigned int count;
		};

	}
}
