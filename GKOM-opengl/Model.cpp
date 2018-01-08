#include "Model.h"


Model::Model(std::shared_ptr<Mesh> objMesh, std::shared_ptr<Material> objMaterial) 
	: mesh(std::move(objMesh)), material(std::move(objMaterial)), additionalTransform(glm::mat4())
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
