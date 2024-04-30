#pragma once

#include <string>

#include "GL/glew.h"

#include "ArObject.h"

using namespace std;
class Nanosuit : public ArObject {
public:
	Nanosuit();
	~Nanosuit();
private:
	void loadModel() override;
};

