#pragma once

#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"

#include "Buffer.h"

class IndexBuffer : public Buffer {
	public:
		IndexBuffer(unsigned int* indices, unsigned int count);
		IndexBuffer(std::vector<unsigned int> indices);
		~IndexBuffer();

		void bind() const;
		void unBind() const;

		inline unsigned int getCount() const { return m_Count; }
	private:
		unsigned int m_Count;
};
