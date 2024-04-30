#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "vendor/stb_image/stb_image.h"
#include "Mesh.h"

using namespace std;

GLint textureFromFile(const char* path, string directory);

class Model {
public:
	Model();
	Model(char* filepath);

	void bind();
	void unBind();
	
	void loadModel(string filepath);
	void draw(Shader modelShader);

	inline vector<Mesh> getMeshes() { return meshes; }
private:
	vector<Mesh> meshes;
	string directory;
	vector<AssimpTexture> texturesLoaded;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<AssimpTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};