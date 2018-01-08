#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	// constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// use/activate the shader
	void use() const;
	unsigned getId() const;

	// utility uniform functions
	void setBoolUniform(const std::string &name, bool value) const;
	void setIntUniform(const std::string &name, int value) const;
	void setFloatUniform(const std::string &name, float value) const;
	void set3FloatUnifor(const std::string &name, float val1, float val2, float val3) const;
	void setMat4Uniform(const std::string &name, glm::mat4 &value) const;

private:
	// the program ID
	unsigned int shaderProgramId;

	std::string getVertexShaderSource(const char* vertexPath);
	std::string getFragmentShaderSource(const char* fragmentPath);
	unsigned getShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);
	unsigned vertexShaderPrepare(const char *fragmentShaderSource);
	void checkShaderCompilation(unsigned shader, const char *shaderType);
	unsigned fragmentShaderPrepare(const char *fragmentShaderSource);
	unsigned shaderProgramPrepare(unsigned vertexShader, unsigned fragmentShader);
	void checkShaderProgramCompilation(unsigned shaderProgram);
};

#endif