#include "Lamp.h"

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

unsigned int indices[] = {
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16,
		17, 18, 19, 20, 21,
		22, 23, 24, 25, 26,
		27, 28, 29, 30, 31
};

// TODO(j-ka11): Move inside class.
VertexBufferLayout vertexBufferLayout = {
	{ShaderDataType::FLOAT3, "position"},
	{ShaderDataType::FLOAT2, "texture"}
};

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f
};

Lamp::Lamp() {
	lightPosition.x = 1.2f;
	lightPosition.y = 1.5f;
	lightPosition.z = 0.0f;

	GLCall(glGenVertexArrays(1, &m_VertexArrayID));
	indexBuffer = new IndexBuffer(indices, 32);
	vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));

	vertexBuffer->setLayout(vertexBufferLayout);
	bind();
	indexBuffer->bind();
	bind();
	vertexBuffer->bind();

	unsigned int index = 0;
	for (const auto& element : vertexBufferLayout.getElements()) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.getComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.type),
			element.normalized ? GL_TRUE : GL_FALSE,
			vertexBufferLayout.getStride(),
			(const void*)element.offset);
		index++;
	}
	unBind();
}

void Lamp::bind() {
	GLCall(glBindVertexArray(m_VertexArrayID));
}

void Lamp::unBind() {
	GLCall(glBindVertexArray(0));
}

void Lamp::draw() {
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr));
}

Lamp::~Lamp() {
	delete indexBuffer;
	delete vertexBuffer;
}
