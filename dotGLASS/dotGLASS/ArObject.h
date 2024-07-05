#pragma once

#include <string>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

using namespace std;
class ArObject {
public:
	ArObject();
	~ArObject();

	void bind();
	void unBind();
	void draw();

	inline vector<Mesh> getMeshes() { return meshes; }
protected:
	string filepath;

	void loadAsset();
private:
	string directory;
	vector<Mesh> meshes;
	vector<AssimpTexture> texturesLoaded;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
