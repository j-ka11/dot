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

namespace dotGLASS {
	namespace Object {

		class ArObject {
			public:
				ArObject();
				~ArObject();

				void bind();
				void unBind();
				void draw();

				inline std::vector<Mesh> getMeshes() { return meshes; }
			protected:
				std::string filepath;

				void loadAsset();
			private:
				std::string directory;
				std::vector<Mesh> meshes;
				std::vector<AssimpTexture> texturesLoaded;

				void processNode(aiNode* node, const aiScene* scene);
				Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		};

	}
}
