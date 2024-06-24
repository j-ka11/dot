#include "Arrow.h"

Arrow::Arrow() {
	filepath = "res/models/arrow.obj";
	loadModel();
}

Arrow::~Arrow() {

}

void Arrow::loadModel() {
	objectModel.loadModel(filepath);
}
