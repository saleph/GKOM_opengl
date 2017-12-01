#ifndef MAIN_H
#define MAIN_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <atomic>
#include <iostream>

void initOpengl();
GLFWwindow *createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void initGlad();
void processInput(GLFWwindow *window);
void currentFpsShow(GLFWwindow* window);

void render(unsigned shaderProgram, unsigned VAO);
unsigned verticesPrepare();
unsigned elementsPrepare();
unsigned getVao();

unsigned getShaderProgram();
unsigned vertexShaderPrepare();
void checkShaderCompilation(unsigned shader, const char *shaderType);
unsigned fragmentShaderPrepare();
unsigned shaderProgramPrepare(unsigned vertexShader, unsigned fragmentShader);
void checkShaderProgramCompilation(unsigned shaderProgram);

#endif // MAIN_H