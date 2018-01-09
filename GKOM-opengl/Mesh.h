#pragma once
#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vertex.h"


class Mesh {
public:
	Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned>&& indices);
	void draw();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;
	unsigned VAO;
	unsigned VBO;
	unsigned EBO;

};