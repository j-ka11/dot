#include "Shader.h"

Shader::Shader(string& filepath) {
	m_FilePath = filepath;
	m_RendererID = 0;

	ShaderProgramSource source = parseShader(filepath);
	GLCall(m_RendererID = createShader(source.VertexSource, source.FragmentSource));
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::parseShader(const string& filepath) {
	ifstream stream(filepath);

	string line;
	stringstream ss[2];

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				//set mode to vertex
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != string::npos) {
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

unsigned int Shader::compileShader(const string& source, unsigned int type) {
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
		string shaderType = "";
		if (type == GL_VERTEX_SHADER) shaderType = "vertex";
		else shaderType = "fragment";
		cout << "Failed to compile " + shaderType + " shader boss" << endl;
		cout << message << endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const string& vertexSource, const string& fragmentSource) {
	GLCall(unsigned int program = glCreateProgram());
	GLCall(unsigned int vs = compileShader(vertexSource, GL_VERTEX_SHADER));
	GLCall(unsigned int fs = compileShader(fragmentSource, GL_FRAGMENT_SHADER));

	GLCall(glAttachShader(program, vs))
		GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::bind() const {
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unBind() const {
	GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const string& name, int value) {
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const string& name, float value) {
	GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform3f(const string& name, float v0, float v1, float v2) {
	GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4(const string& name, const glm::mat4 matrix) {
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		cout << "Warning: Uniform '" << name << "' doesn't exist" << endl;

	m_UniformLocationCache[name] = location;
	return location;
}
