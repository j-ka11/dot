#include "Shader.h"

dotGLASS::Shader::Shader(std::string& filePath) {
	this->filePath = filePath;
	rendererID = 0;

	ShaderProgramSource source = parseShader(filePath);
	GLCall(rendererID = createShader(source.VertexSource, source.FragmentSource));
}

dotGLASS::Shader::~Shader() {
	GLCall(glDeleteProgram(rendererID));
}

void dotGLASS::Shader::bind() const {
	GLCall(glUseProgram(rendererID));
}

unsigned int dotGLASS::Shader::compileShader(const std::string& source, unsigned int type) {
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//error handling
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::string shaderType = "";
		if (type == GL_VERTEX_SHADER) shaderType = "vertex";
		else shaderType = "fragment";
		std::cout << "Failed to compile " + shaderType + " shader boss" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int dotGLASS::Shader::createShader(const std::string& vertexSource, const std::string& fragmentSource) {
	GLCall(unsigned int program = glCreateProgram());
	GLCall(unsigned int vs = compileShader(vertexSource, GL_VERTEX_SHADER));
	GLCall(unsigned int fs = compileShader(fragmentSource, GL_FRAGMENT_SHADER));

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

dotGLASS::ShaderProgramSource dotGLASS::Shader::parseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				//set mode to vertex
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//set mode to fragment
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

void dotGLASS::Shader::unBind() const {
	GLCall(glUseProgram(0));
}

int dotGLASS::Shader::getUniformLocation(const std::string& name) {
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: Uniform '" << name << "' doesn't exist" << std::endl;

	uniformLocationCache[name] = location;
	return location;
}

void dotGLASS::Shader::setUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void dotGLASS::Shader::setUniform1f(const std::string& name, float value) {
	GLCall(glUniform1f(getUniformLocation(name), value));
}

void dotGLASS::Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
	GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void dotGLASS::Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void dotGLASS::Shader::setUniformMat4(const std::string& name, const glm::mat4 matrix) {
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
