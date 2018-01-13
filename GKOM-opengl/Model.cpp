#include "Model.h"


Model::Model(std::shared_ptr<Mesh> objMesh, std::shared_ptr<Texture> objTexture) 
	: mesh(std::move(objMesh)), texture(std::move(objTexture)), additionalTransform(glm::mat4())
{ }

void Model::updateTransform() {
	glm::mat4 unit;
	auto translate = glm::translate(unit, position);
	auto rotate = glm::rotate(translate, rotation.x, glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(rotate, rotation.z, glm::vec3(0, 0, 1));
}

void Model::setPosition(glm::vec3 pos) {
	if (position == pos)
		return;
	position = pos;
	updateTransform();
}

void Model::setRotation(glm::vec3 rot) {
	if (rotation == rot)
		return;
	rotation = rot;
	updateTransform();
}

void Model::draw(const Shader &shaderProgram) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	shaderProgram.setMat4Uniform("model", modelMatrix);
	shaderProgram.setMat4Uniform("additionalTransformation", additionalTransform);
	mesh->draw();
}
