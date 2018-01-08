#include "CubeBuilder.h"

std::shared_ptr<Mesh> CubeBuilder::getMesh() {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices{ 0, 1, 2,
		2, 1, 3,
		4, 5, 6,
		6, 5, 7,
		8, 9, 10,
		10, 9, 11,
		12, 13, 14,
		14, 13, 15,
		16, 17, 18,
		18, 17, 19,
		20, 21, 22,
		22, 21, 23, };

	// front side
	vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(frontMapBegin.x, frontMapBegin.y));
	vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(frontMapEnd.x, frontMapBegin.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(frontMapBegin.x, frontMapEnd.y));
	vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(frontMapEnd.x, frontMapEnd.y));
	// back side
	vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(backMapEnd.x, backMapEnd.y));
	vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(backMapBegin.x, backMapEnd.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(backMapEnd.x, backMapBegin.y));
	vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(backMapBegin.x, backMapBegin.y));
	// top side
	vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(topMapBegin.x, topMapBegin.y));
	vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(topMapEnd.x, topMapBegin.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(topMapBegin.x, topMapEnd.y));
	vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(topMapEnd.x, topMapEnd.y));
	// bottom side
	vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(bottomMapBegin.x, bottomMapBegin.y));
	vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(bottomMapEnd.x, bottomMapBegin.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(bottomMapBegin.x, bottomMapEnd.y));
	vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(bottomMapEnd.x, bottomMapEnd.y));
	// right side
	vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(rightMapBegin.x, rightMapBegin.y));
	vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(rightMapEnd.x, rightMapBegin.y));
	vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(rightMapBegin.x, rightMapEnd.y));
	vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(rightMapEnd.x, rightMapEnd.y));
	// left side
	vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(leftMapBegin.x, leftMapBegin.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(leftMapEnd.x, leftMapBegin.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(leftMapBegin.x, leftMapEnd.y));
	vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(leftMapEnd.x, leftMapEnd.y));

	return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}