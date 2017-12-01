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
#include "Shader.h"

void initOpengl();
GLFWwindow *createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void initGlad();
void processInput(GLFWwindow *window);
void currentFpsShow(GLFWwindow* window);

void render(const Shader &shaderProgram, unsigned VAO);
unsigned verticesPrepare(float *vertices, unsigned size);
unsigned elementsPrepare(unsigned *indices, unsigned size);
unsigned getVao(unsigned vaoNo);

#endif // MAIN_H