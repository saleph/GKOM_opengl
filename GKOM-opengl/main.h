#ifndef MAIN_H
#define MAIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <atomic>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include "Camera.h"
#include "Shader.h"
#include "CylinderBuilder.h"
#include "Model.h"


class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};

class MainScene {
	std::vector<Model> sceneModels;
	std::shared_ptr<Model> light;
public:
	MainScene() = default;
	void setupScene();
	void mainProg();
	void initOpengl();
	GLFWwindow *createWindow();
	void loadLibraries();

	void updateShader(const Shader &shaderProgram);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void currentFpsShow(GLFWwindow* window);

#endif // MAIN_H