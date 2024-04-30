#pragma once

#include <string>

#include "GL/glew.h"

#include "ArObject.h"

using namespace std;
class Arrow : public ArObject {
public:
	Arrow();
	~Arrow();
private:
	void loadModel() override;
};

