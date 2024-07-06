#include "GPU/VertexBuffer.h"

dotGLASS::GPU::VertexBuffer::VertexBuffer(const void* vertices, unsigned int size) {
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

dotGLASS::GPU::VertexBuffer::VertexBuffer(std::vector<Vertex> vertices) {
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex)/* volume(size in bytes) */, &vertices[0], GL_STATIC_DRAW));
}

dotGLASS::GPU::VertexBuffer::~VertexBuffer() {}

void dotGLASS::GPU::VertexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}

void dotGLASS::GPU::VertexBuffer::unBind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
