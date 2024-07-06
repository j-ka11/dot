#include "GPU/IndexBuffer.h"

dotGLASS::GPU::IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count) {
	this->count = count;

	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

dotGLASS::GPU::IndexBuffer::IndexBuffer(std::vector<unsigned int> indices) {
	count = indices.size();

	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int)/* volume (size in bytes) */, &indices[0], GL_STATIC_DRAW));
}

dotGLASS::GPU::IndexBuffer::~IndexBuffer() {}

void dotGLASS::GPU::IndexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
}

void dotGLASS::GPU::IndexBuffer::unBind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
