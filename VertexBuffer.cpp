#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* vertices, unsigned int size) {
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices) {
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex)/* volume(size in bytes) */, &vertices[0], GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

void VertexBuffer::unBind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
