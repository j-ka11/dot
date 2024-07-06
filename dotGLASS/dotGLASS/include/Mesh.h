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

#include "GPU/IndexBuffer.h"
#include "GPU/VertexBuffer.h"
#include "Shader.h"

namespace dotGLASS {

	struct AssimpTexture {
		GLuint id;
		std::string type;
		aiString path;
	};

	class Mesh {
		public:
			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<AssimpTexture> textures);

			void bind();
			void draw(Shader meshShader);
			void unBind();

			inline GPU::IndexBuffer* getIndexBuffer() { return indexBuffer; }
			inline std::vector<Vertex> getVertices() { return vertices; }
		private:
			GPU::IndexBuffer* indexBuffer;
			std::vector<unsigned int> indices;
			VertexBufferLayout layout;
			std::vector<AssimpTexture> textures;
			unsigned int vertexArrayID;
			GPU::VertexBuffer* vertexBuffer;
			std::vector<Vertex> vertices;

			void setupMesh();
	};

}
