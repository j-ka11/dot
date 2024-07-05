#include "../include/Buffer.h"

Buffer::Buffer() {
	GLCall(glGenBuffers(1, &m_BufferID));
}

Buffer::Buffer(const void* vertices, unsigned int size) {
	GLCall(glGenBuffers(1, &m_BufferID));
}

Buffer::Buffer(std::vector<Vertex> vertices) {
	GLCall(glGenBuffers(1, &m_BufferID));
}

Buffer::Buffer(unsigned int* indices, unsigned int count) {
	GLCall(glGenBuffers(1, &m_BufferID));
}

Buffer::Buffer(std::vector<unsigned int> indices) {
	GLCall(glGenBuffers(1, &m_BufferID));
}

Buffer::~Buffer() {
	GLCall(glDeleteBuffers(1, &m_BufferID));
}

void Buffer::bind() const {}

void Buffer::unBind() const {}
