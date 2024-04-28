#include "Nanosuit.h"

Nanosuit::Nanosuit() {
	filepath = "res/models/nanosuit.fbx";
	loadModel();
}

Nanosuit::~Nanosuit() {

}

void Nanosuit::loadModel() {
	objectModel.loadModel(filepath);
}