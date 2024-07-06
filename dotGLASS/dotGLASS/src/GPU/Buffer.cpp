#include "GPU/Buffer.h"

dotGLASS::GPU::Buffer::Buffer() {
	GLCall(glGenBuffers(1, &bufferID));
}

dotGLASS::GPU::Buffer::Buffer(const void* vertices, unsigned int size) {
	GLCall(glGenBuffers(1, &bufferID));
}

dotGLASS::GPU::Buffer::Buffer(std::vector<Vertex> vertices) {
	GLCall(glGenBuffers(1, &bufferID));
}

dotGLASS::GPU::Buffer::Buffer(unsigned int* indices, unsigned int count) {
	GLCall(glGenBuffers(1, &bufferID));
}

dotGLASS::GPU::Buffer::Buffer(std::vector<unsigned int> indices) {
	GLCall(glGenBuffers(1, &bufferID));
}

dotGLASS::GPU::Buffer::~Buffer() {
	GLCall(glDeleteBuffers(1, &bufferID));
}

void dotGLASS::GPU::Buffer::bind() const {}

void dotGLASS::GPU::Buffer::unBind() const {}
