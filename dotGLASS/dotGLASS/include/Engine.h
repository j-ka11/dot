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

#include "Camera.h"
#include "Object/ArObject.h"
#include "Object/Arrow.h"
#include "Object/Lamp.h"
#include "Object/Nanosuit.h"
#include "Shader.h"

namespace dotGLASS {

	class Engine {
		public:
			Engine();
			~Engine();

			void run();
		private:
			GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)

			void doMovement();
			void openWindow();
	};

}
