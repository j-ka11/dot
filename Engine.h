#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC //***THIS LINE NEEDED TO USE GLEW***
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "texture.h"
#include "Camera.h"
#include "ArObject.h"
#include "Arrow.h"
#include "Nanosuit.h"

using namespace std;
class Engine
{
public:
	Engine();
	~Engine();
	void run();
private:
	glm::vec3 lightPos;

	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	void openWindow();
	void doMovement();
};
