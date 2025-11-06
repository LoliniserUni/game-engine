#pragma once

#include "GameObject2D.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject : public GameObject2D
{
protected:
	// Variables
	const float PI = 3.141593f;
	float maxSpeed = 200.0f;
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	float rotSpeed = glm::radians(420.0f);

public:
	// Default constructor
	GameObject() : GameObject2D() {};

	// Constructors
	GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz);
	GameObject(GameObject2D* object);

	// Functions
	void updateVel(double tDelta);
	glm::vec2 getForwardVector();
	void keepOnScreen(float height, float width);
	void setVelocity(glm::vec2 dir, float speed);
	void makeNew(GameObject object);
	bool checkColl(GameObject object);
};

#endif