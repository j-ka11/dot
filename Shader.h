#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>

#include "ErrorDirectives.h"

using namespace std;
struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

class Shader {
private:
	string m_FilePath;
	unsigned int m_RendererID;
	unordered_map<string, int> m_UniformLocationCache;

	int getUniformLocation(const string& name);
	ShaderProgramSource parseShader(const string& filepath);
	unsigned int compileShader(const string& source, unsigned int type);
	unsigned int createShader(const string& vertexSource, const string& fragmentSource);
public:
	Shader(string& filepath);
	~Shader();

	void bind() const;
	void unBind() const;

	//set uniforms
	void setUniform1i(const string& name, int value); //value is the texture slot that we have bound our texture to
	void setUniform1f(const string& name, float value);
	void setUniform3f(const string& name, float v0, float v1, float v2);
	void setUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4(const string& name, const glm::mat4 matrix);
};
