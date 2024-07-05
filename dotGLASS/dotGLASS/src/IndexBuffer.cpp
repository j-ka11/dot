#include "../include/IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count) {
	m_Count = count;

	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(std::vector<unsigned int> indices) {
	m_Count = indices.size();

	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int)/* volume (size in bytes) */, &indices[0], GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {}

void IndexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::unBind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
