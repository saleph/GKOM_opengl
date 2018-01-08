#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;

	Vertex() {};

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 textCoord) :
		position(position), normal(normal), textCoord(textCoord) {}
};
