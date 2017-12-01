#ifndef MAIN_H
#define MAIN_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void initOpengl();
GLFWwindow *createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void initGlad();
void processInput(GLFWwindow *window);

#endif // MAIN_H