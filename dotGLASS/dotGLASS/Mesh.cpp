#include "Mesh.h"

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

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<AssimpTexture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh() {
	// Vertex Array
	GLCall(glGenVertexArrays(1, &m_VertexArrayID));
	bind();

	// Vertex Buffer Layout
	layout = {
		{ShaderDataType::FLOAT3, "position"},
		{ShaderDataType::FLOAT3, "normal"},
		{ShaderDataType::FLOAT2, "texCoords"}
	};

	// Vertex Buffer
	vertexBuffer = new VertexBuffer(vertices);
	vertexBuffer->setLayout(layout);
	vertexBuffer->bind();

	// Index Buffer
	indexBuffer = new IndexBuffer(indices);
	indexBuffer->bind();

	unsigned int index = 0;
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
}

void Mesh::bind() {
	GLCall(glBindVertexArray(m_VertexArrayID));
}

void Mesh::unBind() {
	GLCall(glBindVertexArray(0));
}

void Mesh::draw(Shader meshShader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (int i = 0; i < textures.size(); i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + i));

		stringstream ss;
		string number;
		string name = textures[i].type;

		if (name == "texture_diffuse") {
			ss << diffuseNr++;
		}
		else if (name == "texture_specular") {
			ss << specularNr++;
		}

		number = ss.str();

		meshShader.setUniform1i(name + number, i);
		GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
	}

	//meshShader.setUniform1f("material.shininess", 16.0f);
	GLCall(glBindVertexArray(m_VertexArrayID));
	GLCall(glBindVertexArray(0));

	for (int i = 0; i < textures.size(); i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + i));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
