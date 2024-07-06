#include "Mesh.h"

static GLenum ShaderDataTypeToOpenGLBaseType(dotGLASS::ShaderDataType type) {

	switch (type) {
		case dotGLASS::ShaderDataType::FLOAT:     return GL_FLOAT;
		case dotGLASS::ShaderDataType::FLOAT2:    return GL_FLOAT;
		case dotGLASS::ShaderDataType::FLOAT3:    return GL_FLOAT;
		case dotGLASS::ShaderDataType::FLOAT4:    return GL_FLOAT;
		case dotGLASS::ShaderDataType::MAT3:      return GL_FLOAT;
		case dotGLASS::ShaderDataType::MAT4:      return GL_FLOAT;
		case dotGLASS::ShaderDataType::INT:       return GL_INT;
		case dotGLASS::ShaderDataType::INT2:      return GL_INT;
		case dotGLASS::ShaderDataType::INT3:      return GL_INT;
		case dotGLASS::ShaderDataType::INT4:      return GL_INT;
		case dotGLASS::ShaderDataType::BOOL:      return GL_BOOL;
	}

	return 0;

}

dotGLASS::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<AssimpTexture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void dotGLASS::Mesh::bind() {
	GLCall(glBindVertexArray(vertexArrayID));
}

void dotGLASS::Mesh::draw(dotGLASS::Shader meshShader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (int i = 0; i < textures.size(); i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + i));

		std::stringstream ss;
		std::string number;
		std::string name = textures[i].type;

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
	GLCall(glBindVertexArray(vertexArrayID));
	GLCall(glBindVertexArray(0));

	for (int i = 0; i < textures.size(); i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + i));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}

void dotGLASS::Mesh::setupMesh() {
	// Vertex Array
	GLCall(glGenVertexArrays(1, &vertexArrayID));
	bind();

	// Vertex Buffer Layout
	layout = {
		{ShaderDataType::FLOAT3, "position"},
		{ShaderDataType::FLOAT3, "normal"},
		{ShaderDataType::FLOAT2, "texCoords"}
	};

	// Vertex Buffer
	vertexBuffer = new dotGLASS::GPU::VertexBuffer(vertices);
	vertexBuffer->setLayout(layout);
	vertexBuffer->bind();

	// Index Buffer
	indexBuffer = new dotGLASS::GPU::IndexBuffer(indices);
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

void dotGLASS::Mesh::unBind() {
	GLCall(glBindVertexArray(0));
}
