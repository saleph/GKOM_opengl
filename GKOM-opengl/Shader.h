#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

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
	void use();
	unsigned getId() const;

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

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