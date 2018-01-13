#include "Model.h"


Model::Model(std::shared_ptr<Mesh> objMesh, std::shared_ptr<Texture> objTexture, std::function<glm::mat4(int)> transform)
	: mesh(std::move(objMesh)), texture(std::move(objTexture)), transformGenerator(transform)
{ }

void Model::updateTransform() {
	glm::mat4 unit;
	auto translate = glm::translate(unit, position);
	auto rotate = glm::rotate(translate, rotation.x, glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(rotate, rotation.z, glm::vec3(0, 0, 1));
}

Model& Model::setPosition(glm::vec3 pos) {
	if (position == pos)
		return *this;
	position = pos;
	updateTransform();
	return *this;
}

Model& Model::setRotation(glm::vec3 rot) {
	if (rotation == rot)
		return *this;
	rotation = rot;
	updateTransform();
	return *this;
}

void Model::draw(const Shader &shaderProgram, int transformGenArg) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	shaderProgram.setMat4Uniform("model", modelMatrix);
	shaderProgram.setMat4Uniform("additionalTransformation", transformGenerator(transformGenArg));
	mesh->draw();
}
