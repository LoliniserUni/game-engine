#pragma once

#include "GameObject2D.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class GameObject : public GameObject2D
{
public:
	// Variables
	const float PI = 3.141593f;
	float maxSpeed = 200.0f;
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	float rotSpeed = glm::radians(420.0f);

	// Default constructor
	GameObject() {};

	// Constructors
	GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz) {
		position = pos;
		orientation = ori;
		size = siz;
		textureID = textID;
	};
	GameObject(GameObject2D* object) {
		position = object->position;
		orientation = object->orientation;
		size = object->size;
		textureID = object->textureID;
	};

	// Functions
	void updateVel(double tDelta);
	glm::vec2 getForwardVector();
	void keepOnScreen(float height, float width);
	void setVelocity(glm::vec2 dir, float speed);
	void makeNew(GameObject object);
	bool checkColl(GameObject object);
};