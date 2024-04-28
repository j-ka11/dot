#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<AssimpTexture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh() {
	va = new VertexArray();
	va->bind();
	vb = new VertexBuffer(vertices);
	ib = new IndexBuffer(indices);
	layout = {
		{ShaderDataType::FLOAT3, "position"},
		{ShaderDataType::FLOAT3, "normal"},
		{ShaderDataType::FLOAT2, "texCoords"}
	};
	vb->setLayout(layout);
	va->addVertexBuffer(vb);
	va->addIndexBuffer(ib);
}

void Mesh::bind() {
	va->bind();
}

void Mesh::unBind() {
	va->unBind();
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
	va->bind();
	//meshRenderer.draw(va, ib);
	va->unBind();

	for (int i = 0; i < textures.size(); i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + i));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}