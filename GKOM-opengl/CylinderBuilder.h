#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Mesh.h"

class CylinderBuilder {
private:

	GLfloat mRadius;
	GLfloat mHeight;
	GLuint mSides;

	glm::vec2 mWrapBegin;
	glm::vec2 mWrapEnd;

	glm::vec2 mUpperCapBegin;
	glm::vec2 mUpperCapEnd;

	glm::vec2 mLowerCapBegin;
	glm::vec2 mLowerCapEnd;

public:
	CylinderBuilder() : mRadius(1.0f), mHeight(1.0f), mSides(24) { };

	CylinderBuilder& radius(GLfloat radius) {
		mRadius = radius;
		return *this;
	};

	CylinderBuilder& height(GLfloat height) {
		mHeight = height;
		return *this;
	};

	CylinderBuilder& sides(GLuint sides) {
		mSides = sides;
		return *this;
	};

	CylinderBuilder& wrap(glm::vec2 begin, glm::vec2 end) {
		mWrapBegin = begin;
		mWrapEnd = end;
		return *this;
	};

	CylinderBuilder& upperCap(glm::vec2 begin, glm::vec2 end) {
		mUpperCapBegin = begin;
		mUpperCapEnd = end;
		return *this;
	};

	CylinderBuilder& lowerCap(glm::vec2 begin, glm::vec2 end) {
		mLowerCapBegin = begin;
		mLowerCapEnd = end;
		return *this;
	};

	std::shared_ptr<Mesh> build();
};