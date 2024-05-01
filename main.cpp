//This is the source code for the dot environment
//created by Josh Kall on December 14, 2018, 02:14 AM

// G++ command: g++ -msse2 -IC:\glew-2.1.0\include -IC:\glfw-3.2.1\include -IC:\glm -IC:\Assimp\include -LC:\glew-2.1.0/lib *.cpp

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