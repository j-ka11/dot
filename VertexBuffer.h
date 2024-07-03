#pragma once

#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"

#include "Buffer.h"
#include "VertexBufferLayout.h"

class VertexBuffer : public Buffer {
	public:
		VertexBuffer(const void* vertices, unsigned int size);
		VertexBuffer(std::vector<Vertex> vertices);
		~VertexBuffer();

		void bind() const;
		void unBind() const;

		inline const VertexBufferLayout& getLayout() const { return m_Layout; }
		inline void setLayout(const VertexBufferLayout& layout) { m_Layout = layout; }
	private:
		VertexBufferLayout m_Layout;
};
