#pragma once

#include "Texture.h"
#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Shader.h"

class Model {
public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);

	void setAdditionalTransformation(glm::mat4 transformation) { additionalTransform = transformation; }
	glm::mat4 getAdditionalTransformation() const { return additionalTransform; }

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const { return position; }

	// set the model rotation in each direction (eg. (0, PI/2, 0) will flip from horizontal to vertical)
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation() const { return rotation; }

	void setTexture(std::shared_ptr<Texture>& m) { texture = m; }
	std::shared_ptr<Texture> getTexture() { return texture; }

	void draw(const Shader &shader);

private:
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Texture> texture;
	glm::mat4 additionalTransform;
	glm::mat4 modelMatrix;

	glm::vec3 position;
	glm::vec3 rotation;

	void updateTransform();
};