#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <string>

class Texture {
public:
	static std::shared_ptr<Texture> loadFromFile(const std::string &file);

	Texture(unsigned texture);

	unsigned getID() { return mTextureID; };
private:
	unsigned mTextureID;
};
