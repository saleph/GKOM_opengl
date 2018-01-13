#include "main.h"

std::atomic<unsigned long> fps;
std::atomic<double> frameTimes;

void MainScene::setupScene() {
	const float PI = 3.1415f;
	const float CYLINDER_HEIGHT = 1.0f;
	const float CYLINDER_RADIUS = 2 * CYLINDER_HEIGHT;
	const float TOWER_HEIGHT = 7.0f;
	const float STICK_ANGLE = atan(CYLINDER_RADIUS / (TOWER_HEIGHT - CYLINDER_HEIGHT));
	const float STICK_LEN = (TOWER_HEIGHT - CYLINDER_HEIGHT) / cos(STICK_ANGLE);

	auto cylinderSpinner = [](int multipler) {
		float timeValue = glfwGetTime();
		float normalizedTimeValue = sin(timeValue);

		// rotation trans
		glm::mat4 trans;
		trans = glm::rotate(trans, glm::radians(multipler * timeValue * 200), glm::vec3(0.0f, 0.0f, 1.0f));
		return trans;
	};

	auto stickSpinner = [PI, STICK_LEN, STICK_ANGLE, CYLINDER_HEIGHT](int multipler) {
		float timeValue = glfwGetTime();
		float normalizedTimeValue = sin(timeValue);

		// rotation trans
		glm::mat4 trans;
		float move = STICK_LEN;
		//trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, move));
		trans = glm::rotate(trans, glm::radians(multipler * timeValue * 200), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, STICK_LEN/2));
		trans = glm::rotate(trans, STICK_ANGLE, glm::vec3(1.0, 0.0, 0.0));
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -STICK_LEN/2));
		return trans;

	};

	auto woodTexture = Texture::loadFromFile("Resources\\wood.jpg");

	// cylinder
	sceneModels.push_back(Model(CylinderBuilder()
		.height(CYLINDER_HEIGHT)
		.radius(CYLINDER_RADIUS)
		.smallRadius(0.2f)
		.sides(48)
		.wrap(glm::vec2(0.0, 0), glm::vec2(1, 1))
		.upperCap(glm::vec2(0.0, 0.5), glm::vec2(0.5, 1.0))
		.lowerCap(glm::vec2(0.0, 0.5), glm::vec2(0.5, 1.0))
		.buildWithHole(),
		woodTexture,
		cylinderSpinner)
		.setPosition(glm::vec3(0.0f, 0.0f, CYLINDER_HEIGHT / 2))
		);
	// stick
	sceneModels.push_back(Model(CylinderBuilder()
		.height(STICK_LEN)
		.radius(0.1f)
		.sides(48)
		.wrap(glm::vec2(0.0, 0), glm::vec2(1, 1))
		.upperCap(glm::vec2(0.0, 0.5), glm::vec2(0.5, 1.0))
		.lowerCap(glm::vec2(0.0, 0.5), glm::vec2(0.5, 1.0))
		.buildStandard(),
		woodTexture,
		stickSpinner)
		//.setRotation(glm::vec3(PI / 2.0f, 0.0f, 0.0f))
		.setPosition(glm::vec3(0.0, 0.0, CYLINDER_HEIGHT/2 + (TOWER_HEIGHT-CYLINDER_HEIGHT)/2))
		);
}

// with normals
float verticesCube[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

float verticesCubeTexture[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};

float vertices1[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned indices1[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

float vertices2[] = {
	0.0f, 0.3f, 0.0f,  // top  
	-0.3f, 0.0f, 0.0f,  // bottom left
	0.3f, 0.0f, 0.0f  // bottom right 
};

unsigned indices2[] = {  // note that we start from 0!
	0, 1, 2   // first triangle
};

int main() {
	MainScene mainProg;
	mainProg.mainProg();
}

void MainScene::mainProg()
{
	initOpengl();
	GLFWwindow* window = createWindow();
	loadLibraries();

	// line/fill setting
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	unsigned VAO2 = getVao(2); // light
	unsigned VAO1 = getVao(3); // cubes
	unsigned texture = loadMinmapTexture("Resources\\wood.jpg");

	Shader objectsShader("lighting.vert", "lighting.frag");
	Shader lightSourceShader("lightSource.vert", "lightSource.frag");

	std::async(std::launch::async, currentFpsShow, window);
	setupScene();
	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		Timer t;

		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render(2, lightSourceShader, VAO1, -1);
		render(1, objectsShader, VAO1, texture);

		glfwSwapBuffers(window);
		glfwPollEvents();
		++fps;
		frameTimes = frameTimes + t.elapsed();
	}

	glfwTerminate();
}

void MainScene::initOpengl() {
	if (glfwInit() != GL_TRUE) {
		std::cout << "GLFW initialization failed" << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	std::cout << ">> OpenGL initialized" << std::endl;
}

GLFWwindow *MainScene::createWindow() {
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

void MainScene::loadLibraries() {
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
		std::cout << "FPS: " << fps << "\t Frame time: " << std::setprecision(2) << frameTimes * 1000.0 / fps << " ms" << std::endl;
		fps = 0;
		frameTimes = 0;
	}
}

void MainScene::render(int vaoType, const Shader &shaderProgram, unsigned VAO, int texture) {
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	// rotation trans
	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(greenValue * 360), glm::vec3(greenValue*greenValue, greenValue * 2, greenValue*5));
	//trans = glm::scale(trans, glm::vec3(0.8, 0.8, 0.5));

	// model
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// view
	float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	//glm::vec3 viewPosition = glm::vec3(camX, 0.0, camZ);
	glm::vec3 viewPosition = glm::vec3(10.0f, 10.0, 10.0f);
	glm::mat4 view;

	view = glm::lookAt(viewPosition, glm::vec3(0.0, 0.0, 0.0), glm::vec3
		(0.0, 0.0, 1.0));

	// projection
	glm::mat4 projection;
	float screenWidth = 800.0;
	float screenHeight = 600.0;
	projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);

	// light position
	glm::vec3 lightPos(7.0, -7.0, 7.0);

	shaderProgram.setMat4Uniform("model", model);
	shaderProgram.setMat4Uniform("view", view);
	shaderProgram.setMat4Uniform("projection", projection);
	shaderProgram.setMat4Uniform("transform", trans);
	shaderProgram.setFloatUniform("uniColor", greenValue);
	shaderProgram.set3FloatUniform("lightPos", lightPos);
	shaderProgram.set3FloatUniform("objectColor", 1.0f, 0.5f, 0.31f);
	shaderProgram.set3FloatUniform("lightColor", 1.0f, 1.0f, 1.0f);
	shaderProgram.set3FloatUniform("viewPos", viewPosition);
	shaderProgram.use();

	if (vaoType == 1) {
		for (unsigned int i = 0; i < 1; i++)
		{
			for (auto &&model : sceneModels) {
				model.draw(shaderProgram);
			}
			
		}
	}
	else { // light
		glBindVertexArray(VAO);
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		shaderProgram.setMat4Uniform("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

unsigned MainScene::getVao(unsigned vaoNo) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use

	if (vaoNo == 1 || vaoNo == 2) {
		// same for 1 and 2
		unsigned vertSize = vaoNo == 1 ? sizeof(vertices1) : sizeof(vertices2);
		unsigned elementsSize = vaoNo == 1 ? sizeof(indices1) : sizeof(indices2);

		unsigned VBO = verticesPrepare(vaoNo == 1 ? vertices1 : vertices2, vertSize);
		unsigned EBO = elementsPrepare(vaoNo == 1 ? indices1 : indices2, elementsSize);
	}
	// 3. then set our vertex attributes pointers
	if (vaoNo == 1) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	} 
	else if (vaoNo == 2) { // light
		unsigned vertSize = sizeof(verticesCube);
		unsigned VBO = verticesPrepare(verticesCube, vertSize);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	else if (vaoNo == 3) {
		unsigned vertSize = sizeof(verticesCube);
		unsigned VBO = verticesPrepare(verticesCube, vertSize);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	return VAO;
}

unsigned MainScene::verticesPrepare(float *vertices, unsigned size) {
	unsigned VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	return VBO;
}

unsigned MainScene::elementsPrepare(unsigned *indices, unsigned size) {
	unsigned EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	return EBO;
}

unsigned MainScene::loadMinmapTexture(const char* fname) {
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr) {
		std::cout << "ERROR::TEXTURE::CAN'T_LOAD: " << fname << std::endl;
		exit(-1);
	}

	unsigned texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}