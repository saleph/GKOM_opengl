#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode = getVertexShaderSource(vertexPath);
	std::string fragmentCode = getFragmentShaderSource(fragmentPath);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	shaderProgramId = getShaderProgram(vShaderCode, fShaderCode);
	std::cout << ">> Shader loaded: " << vertexPath << "; " << fragmentPath << std::endl;
}

std::string Shader::getVertexShaderSource(const char* vertexPath) {
	std::string vertexCode;
	std::ifstream vShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open files
		vShaderFile.open(vertexPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	return vertexCode;
}

std::string Shader::getFragmentShaderSource(const char* fragmentPath) {
	std::string fragmentCode;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 	{
		// open files
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		fShaderFile.close();
		// convert stream into string
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return fragmentCode;
}

unsigned Shader::getShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
	unsigned vertexShader = vertexShaderPrepare(vertexShaderSource);
	unsigned fragmentShader = fragmentShaderPrepare(fragmentShaderSource);
	unsigned shaderProgram = shaderProgramPrepare(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

unsigned Shader::vertexShaderPrepare(const char *vertexShaderSource) {
	unsigned vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompilation(vertexShader, "VERTEX");
	return vertexShader;
}

void Shader::checkShaderCompilation(unsigned shader, const char *shaderType) {
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		exit(-1);
	}
}

unsigned Shader::fragmentShaderPrepare(const char *fragmentShaderSource) {
	unsigned fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader, "FRAGMENT");
	return fragmentShader;
}

unsigned Shader::shaderProgramPrepare(unsigned vertexShader, unsigned fragmentShader) {
	unsigned shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderProgramCompilation(shaderProgram);
	return shaderProgram;
}

void Shader::checkShaderProgramCompilation(unsigned shaderProgram) {
	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		exit(-1);
	}
}

void Shader::use() const {
	glUseProgram(shaderProgramId);
}

void Shader::setBoolUniform(const std::string &name, bool value) const {
	use();
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
}

void Shader::setIntUniform(const std::string &name, int value) const {
	use();
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::setFloatUniform(const std::string &name, float value) const {
	use();
	glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}