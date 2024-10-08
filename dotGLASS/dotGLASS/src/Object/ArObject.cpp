#include "Object/ArObject.h"

dotGLASS::Object::ArObject::ArObject() {}

dotGLASS::Object::ArObject::~ArObject() {}

void dotGLASS::Object::ArObject::bind() {
	for (int i = 0; i < meshes.size(); i++) {
		meshes.at(i).bind();
	}
}

void dotGLASS::Object::ArObject::draw() {
	for (int i = 0; i < meshes.size(); i++) {
		Mesh mesh = meshes.at(i);
		mesh.bind();
		GLCall(glDrawElements(GL_TRIANGLES, mesh.getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr));
	}
}

void dotGLASS::Object::ArObject::loadAsset() {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = filepath.substr(0, filepath.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

dotGLASS::Mesh dotGLASS::Object::ArObject::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<AssimpTexture> textures;

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

	return Mesh(vertices, indices, textures);
}

void dotGLASS::Object::ArObject::processNode(aiNode* node, const aiScene* scene) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

void dotGLASS::Object::ArObject::unBind() {
	for (int i = 0; i < meshes.size(); i++) {
		meshes.at(i).unBind();
	}
}
