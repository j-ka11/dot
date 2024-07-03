#include "VertexArray.h"

using namespace std;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {

	switch (type) {
	case ShaderDataType::FLOAT:     return GL_FLOAT;
	case ShaderDataType::FLOAT2:    return GL_FLOAT;
	case ShaderDataType::FLOAT3:    return GL_FLOAT;
	case ShaderDataType::FLOAT4:    return GL_FLOAT;
	case ShaderDataType::MAT3:      return GL_FLOAT;
	case ShaderDataType::MAT4:      return GL_FLOAT;
	case ShaderDataType::INT:       return GL_INT;
	case ShaderDataType::INT2:      return GL_INT;
	case ShaderDataType::INT3:      return GL_INT;
	case ShaderDataType::INT4:      return GL_INT;
	case ShaderDataType::BOOL:      return GL_BOOL;
	}

	return 0;

}

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

void VertexArray::bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unBind() const {
	GLCall(glBindVertexArray(0));
}

void VertexArray::addIndexBuffer(IndexBuffer* indexBuffer) {
	GLCall(glBindVertexArray(m_RendererID));
	indexBuffer->bind();

	this->indexBuffer = indexBuffer;
}

void VertexArray::addVertexBuffer(VertexBuffer* vertexBuffer) {
	GLCall(glBindVertexArray(m_RendererID));
	vertexBuffer->bind();

	unsigned int index = 0;
	const auto& layout = vertexBuffer->getLayout();
	for (const auto& element : layout.getElements()) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.getComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.type),
			element.normalized ? GL_TRUE : GL_FALSE,
			layout.getStride(),
			(const void*)element.offset);
		index++;
	}

	vertexBuffers.push_back(vertexBuffer);
}
