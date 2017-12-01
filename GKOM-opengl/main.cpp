#include "main.h"

std::atomic<unsigned long long> fps;


float vertices1[] = {
	// positions         // colors
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,   
	-0.8f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,  
	-0.2f, -0.2f, 0.0f,	0.0f, 0.0f, 1.0f   
};

float vertices2[] = {
	0.5f, 0.5f, 0.0f,  // top  
	0.2f, -0.2f, 0.0f,  // bottom left
	0.8f, -0.2f, 0.0f,  // bottom right 
};

unsigned indices1[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
};

unsigned indices2[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
};

int main()
{
	initOpengl();
	GLFWwindow* window = createWindow();
	initGlad();

	// line/fill setting
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	unsigned VAO1 = getVao(1);
	unsigned VAO2 = getVao(2);

	Shader shader1("vertexShader1.vert", "fragmentShader1.frag");
	Shader shader2("vertexShader1.vert", "fragmentShader2.frag");

	std::async(std::launch::async, currentFpsShow, window);

	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {
		++fps;
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render(shader1, VAO1);
		render(shader2, VAO2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void initOpengl() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	std::cout << ">> OpenGL initialized" << std::endl;
}

GLFWwindow *createWindow() {
	GLFWwindow* window = glfwCreateWindow(800, 600, "Tomasz Galecki OPENGL project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	// set resize callback
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	std::cout << ">> Window created" << std::endl;

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// resize callback
	glViewport(0, 0, width, height);
}

void initGlad() {
	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	std::cout << ">> GLAD initialized" << std::endl;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void currentFpsShow(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window)) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "FPS: " << fps << std::endl;
		fps = 0;
	}
}

void render(const Shader &shaderProgram, unsigned VAO) {
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	shaderProgram.setFloatUniform("ourColor", greenValue);
	shaderProgram.use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

unsigned getVao(unsigned vaoNo) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use

	// same for 1 and 2
	unsigned vertSize = vaoNo == 1 ? sizeof(vertices1) : sizeof(vertices2);
	unsigned elementsSize = sizeof(indices2);

	unsigned VBO = verticesPrepare(vaoNo == 1 ? vertices1 : vertices2, vertSize);
	unsigned EBO = elementsPrepare(vaoNo == 1 ? indices1 : indices1, elementsSize);
	// 3. then set our vertex attributes pointers
	if (vaoNo == 2) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	} else {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	return VAO;
}

unsigned verticesPrepare(float *vertices, unsigned size) {
	unsigned VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	return VBO;
}

unsigned elementsPrepare(unsigned *indices, unsigned size) {
	unsigned EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	return EBO;
}
