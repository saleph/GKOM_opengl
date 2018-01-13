#include "main.h"
#include "CubeBuilder.h"

std::atomic<unsigned long> fps;
std::atomic<double> frameTimes;
int SPIN_DIRECTION = 1;
float CAMERA_Z = 5.0f;

void MainScene::setupScene() {
	const float ROTATION_SPEED = 300.0f;
	const float PI = 3.1415f;
	const float CYLINDER_HEIGHT = 1.0f;
	const float TOWER_HEIGHT = 5.0f;
	const float CYLINDER_RADIUS = 2 * CYLINDER_HEIGHT;
	const float STICK_ANGLE = atan(CYLINDER_RADIUS / (TOWER_HEIGHT - CYLINDER_HEIGHT));
	const float STICK_LEN = (TOWER_HEIGHT - CYLINDER_HEIGHT) / cos(STICK_ANGLE);

	const float BASE_LENGTH = CYLINDER_RADIUS * 7;
	const float CUBES_HEIGHT = CYLINDER_HEIGHT;
	const float BASE_WIDTH = CYLINDER_RADIUS * 3;

	auto cylinderSpinner = [ROTATION_SPEED](int multipler) {
		float timeValue = glfwGetTime();
		float normalizedTimeValue = sin(timeValue);

		// rotation trans
		glm::mat4 trans;
		trans = glm::rotate(trans, glm::radians(multipler * timeValue * ROTATION_SPEED), glm::vec3(0.0f, 0.0f, 1.0f));
		return trans;
	};

	auto stickSpinner = [PI, STICK_LEN, STICK_ANGLE, CYLINDER_HEIGHT, ROTATION_SPEED](int multipler) {
		float timeValue = glfwGetTime();
		float normalizedTimeValue = sin(timeValue);

		// rotation trans
		glm::mat4 trans;
		float move = STICK_LEN;
		//trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, move));
		trans = glm::rotate(trans, glm::radians(multipler * timeValue * ROTATION_SPEED), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, STICK_LEN/2));
		trans = glm::rotate(trans, STICK_ANGLE, glm::vec3(1.0, 0.0, 0.0));
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -STICK_LEN/2));
		return trans;

	};

	auto woodTexture = Texture::loadFromFile("Resources\\wood.jpg");
	auto brushedTexture = Texture::loadFromFile("Resources\\brushed.jpg");

	glm::vec3 lightPos(7.0, -7.0, 7.0);
	light = std::make_shared<Model>(Model(CubeBuilder()
		.setDepth(0.2)
		.setHeight(0.2)
		.setWidth(0.2)
		.getMesh(),
		brushedTexture)
		.setPosition(lightPos));
	
	// cylinder
	sceneModels.push_back(Model(CylinderBuilder()
		.height(CYLINDER_HEIGHT)
		.radius(CYLINDER_RADIUS + 0.3f)
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
		.setPosition(glm::vec3(0.0, 0.0, CYLINDER_HEIGHT/2 + (TOWER_HEIGHT-CYLINDER_HEIGHT)/2))
		);
	// base
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(CUBES_HEIGHT)
		.setHeight(BASE_WIDTH)
		.setWidth(BASE_LENGTH)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		woodTexture
		)
		.setPosition(glm::vec3(-BASE_LENGTH/4, 0.0f, -CUBES_HEIGHT / 2))
		);
	// tower
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(TOWER_HEIGHT)
		.setHeight(BASE_WIDTH/4)
		.setWidth(BASE_WIDTH / 4)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		woodTexture
		)
		.setPosition(glm::vec3(-BASE_LENGTH / 1.7, 0.0f, TOWER_HEIGHT / 2))
		);
	// horizontal arm
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(BASE_WIDTH / 4)
		.setHeight(BASE_WIDTH / 4)
		.setWidth(BASE_LENGTH/1.3)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		woodTexture
		)
		.setPosition(glm::vec3(-BASE_LENGTH/3.9, 0.0f, TOWER_HEIGHT + (BASE_WIDTH / 4) / 3.2))
		);


	const float BOX_SIZE = 40.0f;
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(1)
		.setHeight(BOX_SIZE)
		.setWidth(BOX_SIZE)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		brushedTexture
		)
		.setPosition(glm::vec3(0.0f, 0.0f, -(CUBES_HEIGHT+0.5f)))
		);
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(BOX_SIZE)
		.setHeight(1)
		.setWidth(BOX_SIZE)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		brushedTexture
		)
		.setPosition(glm::vec3(0, BOX_SIZE/2.1, BOX_SIZE/2.3))
		);
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(BOX_SIZE)
		.setHeight(1)
		.setWidth(BOX_SIZE)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		brushedTexture
		)
		.setPosition(glm::vec3(0, -BOX_SIZE / 2.1, BOX_SIZE / 2.3))
		);
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(BOX_SIZE)
		.setHeight(BOX_SIZE)
		.setWidth(1)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		brushedTexture
		)
		.setPosition(glm::vec3(-BOX_SIZE / 2.1, 0, BOX_SIZE / 2.3))
		);
	sceneModels.push_back(Model(CubeBuilder()
		.setDepth(BOX_SIZE)
		.setHeight(BOX_SIZE)
		.setWidth(1)
		.topMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.frontMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.backMap(glm::vec2(0, 0), glm::vec2(1, 1))
		.getMesh(),
		brushedTexture
		)
		.setPosition(glm::vec3(BOX_SIZE / 2.1, 0, BOX_SIZE / 2.3))
		);
}


int main() {
	MainScene mainProg;
	mainProg.mainProg();
}

void MainScene::mainProg()
{
	initOpengl();
	GLFWwindow* window = createWindow();
	loadLibraries();

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

		// draw objects
		updateShader(objectsShader);
		for (auto &&model : sceneModels) {
			model.draw(objectsShader, SPIN_DIRECTION);
		}
		// draw light
		light->draw(lightSourceShader);

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		SPIN_DIRECTION = 1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		SPIN_DIRECTION = -1;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		CAMERA_Z += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		CAMERA_Z -= 0.4f;

	if (CAMERA_Z <= 0.1f) CAMERA_Z = 0.1f;
}

void currentFpsShow(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window)) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "FPS: " << fps << "\t Frame time: " << std::setprecision(2) << frameTimes * 1000.0 / fps << " ms" << std::endl;
		fps = 0;
		frameTimes = 0;
	}
}

void MainScene::updateShader(const Shader &shaderProgram) {
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	// rotation trans
	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(greenValue * 360), glm::vec3(greenValue*greenValue, greenValue * 2, greenValue * 5));
	//trans = glm::scale(trans, glm::vec3(0.8, 0.8, 0.5));

	// model
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// view
	float radius = 17.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	//glm::vec3 viewPosition = glm::vec3(camX, 0.0, camZ);
	glm::vec3 viewPosition = glm::vec3(camX, camZ, CAMERA_Z);
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
}
