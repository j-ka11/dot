#pragma once

#include <string>

#include "GL/glew.h"

#include "Model.h"

using namespace std;
class ArObject {
public:
	ArObject();
	~ArObject();

	inline Model getModel() { return objectModel; }
protected:
	string filepath;
	Model objectModel;
private:
	virtual void loadModel();
};

