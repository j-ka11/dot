#include "Model.h"

Model::Model() {

}

Model::Model(char* filepath) {
	loadModel(filepath);
}

void Model::bind() {
	for (int i = 0; i < meshes.size(); i++) {
		meshes.at(i).bind();
	}
}

void Model::unBind() {
	for (int i = 0; i < meshes.size(); i++) {
		meshes.at(i).unBind();
	}
}

void Model::draw(Shader modelShader) {
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(modelShader);
	}
}

void Model::loadModel(string filepath) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	directory = filepath.substr(0, filepath.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<AssimpTexture> textures;

	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.positions = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normals = vector;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;

			vertex.texCoords = vec;
		}
		else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	/*if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<AssimpTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<AssimpTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}*/

	return Mesh(vertices, indices, textures);
}

vector<AssimpTexture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
	vector<AssimpTexture> textures;

	for (int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (int j = 0; j < texturesLoaded.size(); j++) {
			if (texturesLoaded[j].path == str) {
				textures.push_back(texturesLoaded[j]);
				skip = true;

				break;
			}
		}

		if (!skip) {
			AssimpTexture texture;
			texture.id = textureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);

			texturesLoaded.push_back(texture);
		}
	}

	return textures;
}

GLint textureFromFile(const char* path, string directory) {
	string filename = string(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	GLCall(glGenTextures(1, &textureID));

	int width, height, bpp;
	unsigned char* image;

	stbi_set_flip_vertically_on_load(1);
	image = stbi_load(filename.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

	GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (image) {
		stbi_image_free(image);
	}

	return textureID;
}
