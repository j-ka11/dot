//This is the source code for the dot environment
//created by Josh Kall on December 14, 2018, 02:14 AM

#include <iostream>
#include <string>

#define GLEW_STATIC //***THIS LINE NEEDED TO USE GLEW***
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Engine.h"

using namespace std;
int main() {

	Engine arEngine;
	arEngine.run();

	return 0;
}