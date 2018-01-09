#include "CylinderBuilder.h"
#include <glm/gtc/constants.hpp>
#include <cmath>
#include <glm/geometric.hpp>
#include "CylinderBuilder.h"

std::shared_ptr<Mesh> CylinderBuilder::buildWithHole() {

	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	float deltaAngle = glm::two_pi<float>() / mSides;

	float deltaU = (mWrapEnd.x - mWrapBegin.x) / mSides;

	float radiusesRatio = mSmallRadius / mBigRadius;

	// outer side
	for (unsigned i = 0; i <= mSides; ++i) {
		float x = mBigRadius * std::cos(deltaAngle * i);
		float y = mBigRadius * std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(x, y, -mHeight / 2), glm::normalize(glm::vec3(x, y, 0)),
			mWrapBegin.x + glm::vec2(i * deltaU, mWrapBegin.y));
		vertices.emplace_back(glm::vec3(x, y, mHeight / 2), glm::normalize(glm::vec3(x, y, 0)),
			mWrapBegin.x + glm::vec2(i * deltaU, mWrapEnd.y));
	}

	indices.emplace_back(0);
	indices.emplace_back(2);
	indices.emplace_back(1);

	for (unsigned i = 0; i < 2 * mSides - 1; ++i) {
		indices.emplace_back(2 * ((i + 2) / 2));
		indices.emplace_back(i + 3);
		indices.emplace_back(2 * ((i + 1) / 2) + 1);
	}

	// inter side
	unsigned interSideFirstIdx = (unsigned)vertices.size();
	for (unsigned i = 0; i <= mSides; ++i) {
		float x = mSmallRadius * std::cos(deltaAngle * i);
		float y = mSmallRadius * std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(x, y, -mHeight / 2), glm::normalize(-1.0f * glm::vec3(x, y, 0)),
			mWrapBegin.x + glm::vec2(i * deltaU, mWrapBegin.y));
		vertices.emplace_back(glm::vec3(x, y, mHeight / 2), glm::normalize(-1.0f * glm::vec3(x, y, 0)),
			mWrapBegin.x + glm::vec2(i * deltaU, mWrapEnd.y));
	}


	indices.emplace_back(interSideFirstIdx + 0);
	indices.emplace_back(interSideFirstIdx + 2);
	indices.emplace_back(interSideFirstIdx + 1);

	for (unsigned i = 0; i < 2 * mSides - 1; ++i) {
		indices.emplace_back(interSideFirstIdx + 2 * ((i + 2) / 2));
		indices.emplace_back(interSideFirstIdx + i + 3);
		indices.emplace_back(interSideFirstIdx + 2 * ((i + 1) / 2) + 1);
	}
	
	// Bottom cap
	unsigned bottomCapFirstIdx = (unsigned)vertices.size();

	glm::vec2 lowerTextureCenter(mUpperCapBegin + (mUpperCapEnd - mUpperCapBegin) * 0.5f);
	float lowerTextureSize = mUpperCapEnd.x - mUpperCapBegin.x;


	vertices.emplace_back(glm::vec3(0, 0, -mHeight / 2), glm::vec3(0, 0, -1), lowerTextureCenter);
	for (unsigned i = 0; i <= mSides; ++i) {
		float x = std::cos(deltaAngle * i);
		float y = std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(x * mBigRadius, y * mBigRadius, -mHeight / 2),
			glm::vec3(0, 0, -1),
			glm::vec2(lowerTextureCenter.x + (x / 2) * lowerTextureSize,
			lowerTextureCenter.y + (-y / 2) * lowerTextureSize));

		vertices.emplace_back(glm::vec3(x * mSmallRadius, y * mSmallRadius, -mHeight / 2),
			glm::vec3(0, 0, -1),
			glm::vec2(lowerTextureCenter.x + (x / 2) * lowerTextureSize * radiusesRatio,
			lowerTextureCenter.y + (-y / 2) * lowerTextureSize * radiusesRatio));
	}

	indices.emplace_back(bottomCapFirstIdx + 0);
	indices.emplace_back(bottomCapFirstIdx + 2);
	indices.emplace_back(bottomCapFirstIdx + 1);

	for (unsigned i = 0; i < 2 * mSides; ++i) {
		indices.emplace_back(bottomCapFirstIdx + 2 * ((i + 2) / 2));
		indices.emplace_back(bottomCapFirstIdx + i + 3);
		indices.emplace_back(bottomCapFirstIdx + 2 * ((i + 1) / 2) + 1);
	}

	
	//Upper cap
	glm::vec2 upperTextureCenter(mUpperCapBegin + (mUpperCapEnd - mUpperCapBegin) * 0.5f);
	float upperTextureSize = mUpperCapEnd.x - mUpperCapBegin.x;

	unsigned upperCapFirstIdx = (unsigned)vertices.size();
	vertices.emplace_back(glm::vec3(0, 0, mHeight / 2), glm::vec3(0, 0, 1), lowerTextureCenter);
	for (unsigned i = 0; i <= mSides; ++i) {
		float x = std::cos(deltaAngle * i);
		float y = std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(mBigRadius * x, mBigRadius * y, mHeight / 2),
			glm::vec3(0, 0, 1),
			glm::vec2(upperTextureCenter.x + (x / 2) * upperTextureSize,
			upperTextureCenter.y + (-y / 2) * upperTextureSize));

		vertices.emplace_back(glm::vec3(mSmallRadius * x, mSmallRadius * y, mHeight / 2),
			glm::vec3(0, 0, 1),
			glm::vec2(upperTextureCenter.x + (x / 2) * upperTextureSize * radiusesRatio,
			upperTextureCenter.y + (-y / 2) * upperTextureSize * radiusesRatio));
	}

	indices.emplace_back(upperCapFirstIdx + 0);
	indices.emplace_back(upperCapFirstIdx + 2);
	indices.emplace_back(upperCapFirstIdx + 1);

	for (unsigned i = 0; i < 2 * mSides; ++i) {
		indices.emplace_back(upperCapFirstIdx + i + 3);
		indices.emplace_back(upperCapFirstIdx + 2 * ((i + 2) / 2));
		indices.emplace_back(upperCapFirstIdx + 2 * ((i + 1) / 2) + 1);
	}

	return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}

std::shared_ptr<Mesh> CylinderBuilder::buildStandard() {

	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	float deltaAngle = glm::two_pi<float>() / mSides;

	float deltaU = (mWrapEnd.x - mWrapBegin.x) / mSides;


	for (unsigned i = 0; i <= mSides; ++i) {
		float x = mBigRadius * std::cos(deltaAngle * i);
		float y = mBigRadius * std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(x, y, -mHeight / 2), glm::normalize(glm::vec3(x, y, 0)),
			mWrapBegin.x + glm::vec2(i * deltaU, mWrapBegin.y));
		vertices.emplace_back(glm::vec3(x, y, mHeight / 2), glm::normalize(glm::vec3(x, y, 0)),
			mWrapBegin.x + glm::vec2(i * deltaU, mWrapEnd.y));
	}

	indices.emplace_back(0);
	indices.emplace_back(2);
	indices.emplace_back(1);

	for (unsigned i = 0; i < 2 * mSides - 1; ++i) {
		indices.emplace_back(2 * ((i + 2) / 2));
		indices.emplace_back(i + 3);
		indices.emplace_back(2 * ((i + 1) / 2) + 1);
	}

	// Caps
	unsigned centerIdx = (unsigned)vertices.size();

	glm::vec2 lowerTextureCenter(mUpperCapBegin + (mUpperCapEnd - mUpperCapBegin) * 0.5f);
	float lowerTextureSize = mUpperCapEnd.x - mUpperCapBegin.x;


	vertices.emplace_back(glm::vec3(0, 0, -mHeight / 2), glm::vec3(0, 0, -1), lowerTextureCenter);
	for (unsigned i = 0; i <= mSides; ++i) {
		float x = std::cos(deltaAngle * i);
		float y = std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(x * mBigRadius, y * mBigRadius, -mHeight / 2),
			glm::vec3(0, 0, -1),
			glm::vec2(lowerTextureCenter.x + (x / 2) * lowerTextureSize,
			lowerTextureCenter.y + (-y / 2) * lowerTextureSize));
	}

	for (unsigned i = 1; i < mSides + 1; ++i) {
		indices.emplace_back(centerIdx);
		indices.emplace_back(centerIdx + i);
		indices.emplace_back(centerIdx + i + 1);
	}


	//Upper cap
	glm::vec2 upperTextureCenter(mUpperCapBegin + (mUpperCapEnd - mUpperCapBegin) * 0.5f);
	float upperTextureSize = mUpperCapEnd.x - mUpperCapBegin.x;

	centerIdx = (unsigned)vertices.size();
	vertices.emplace_back(glm::vec3(0, 0, mHeight / 2), glm::vec3(0, 0, 1), lowerTextureCenter);
	for (unsigned i = 0; i <= mSides; ++i) {
		float x = std::cos(deltaAngle * i);
		float y = std::sin(deltaAngle * i);

		vertices.emplace_back(glm::vec3(mBigRadius * x, mBigRadius * y, mHeight / 2),
			glm::vec3(0, 0, 1),
			glm::vec2(upperTextureCenter.x + (x / 2) * upperTextureSize,
			upperTextureCenter.y + (-y / 2) * upperTextureSize));
	}

	for (unsigned i = 1; i < mSides + 1; ++i) {
		indices.emplace_back(centerIdx);
		indices.emplace_back(centerIdx + i);
		indices.emplace_back(centerIdx + i + 1);
	}


	return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}