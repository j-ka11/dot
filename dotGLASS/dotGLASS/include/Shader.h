#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <malloc.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ErrorDirectives.h"

namespace dotGLASS {

	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader {
		public:
			Shader(std::string& filePath);
			~Shader();

			void bind() const;
			void unBind() const;

			//set uniforms
			void setUniform1i(const std::string& name, int value); //value is the texture slot that we have bound our texture to
			void setUniform1f(const std::string& name, float value);
			void setUniform3f(const std::string& name, float v0, float v1, float v2);
			void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
			void setUniformMat4(const std::string& name, const glm::mat4 matrix);
		private:
			std::string filePath;
			unsigned int rendererID;
			std::unordered_map<std::string, int> uniformLocationCache;

			unsigned int compileShader(const std::string& source, unsigned int type);
			unsigned int createShader(const std::string& vertexSource, const std::string& fragmentSource);
			ShaderProgramSource parseShader(const std::string& filepath);

			int getUniformLocation(const std::string& name);
	};

}
