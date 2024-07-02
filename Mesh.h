#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/types.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBuffer.h"

using namespace std;
struct AssimpTexture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<AssimpTexture> textures);

	void bind();
	void unBind();

	void draw(Shader meshShader);
	inline vector<Vertex> getVertices() { return vertices; }
	inline IndexBuffer* getIB() { return ib; }
private:
	unsigned int m_VertexArrayID;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexBufferLayout layout;

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<AssimpTexture> textures;

	void setupMesh();
};
