#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Mesh.h"

class CubeBuilder {
private:

public:
	CubeBuilder() : width(1), height(1), depth(1) {};

	CubeBuilder& setWidth(float w) {
		width = w;
		return *this;
	};

	CubeBuilder& setHeight(float h) {
		height = h;
		return *this;
	};

	CubeBuilder& setDepth(float d) {
		depth = d;
		return *this;
	}

	CubeBuilder& frontMap(glm::vec2 begin, glm::vec2 end) {
		frontMapBegin = begin;
		frontMapEnd = end;
		return *this;
	}
	CubeBuilder& backMap(glm::vec2 begin, glm::vec2 end) {
		backMapBegin = begin;
		backMapEnd = end;
		return *this;
	}

	CubeBuilder& topMap(glm::vec2 begin, glm::vec2 end) {
		topMapBegin = begin;
		topMapEnd = end;
		return *this;
	}
	CubeBuilder& bottomMap(glm::vec2 begin, glm::vec2 end) {
		bottomMapBegin = begin;
		bottomMapEnd = end;
		return *this;
	}
	CubeBuilder& leftMap(glm::vec2 begin, glm::vec2 end) {
		leftMapBegin = begin;
		leftMapEnd = end;
		return *this;
	}
	CubeBuilder& rightMap(glm::vec2 begin, glm::vec2 end) {
		rightMapBegin = begin;
		rightMapEnd = end;
		return *this;
	}

	std::shared_ptr<Mesh> getMesh();
private:
	float width;
	float height;
	float depth;

	// map positions
	glm::vec2 frontMapBegin;
	glm::vec2 frontMapEnd;

	glm::vec2 backMapBegin;
	glm::vec2 backMapEnd;

	glm::vec2 topMapBegin;
	glm::vec2 topMapEnd;

	glm::vec2 bottomMapBegin;
	glm::vec2 bottomMapEnd;

	glm::vec2 leftMapBegin;
	glm::vec2 leftMapEnd;

	glm::vec2 rightMapBegin;
	glm::vec2 rightMapEnd;
};