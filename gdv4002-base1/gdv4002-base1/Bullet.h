#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class Bullet : public GameObject
{
public:
	// Variables
	float maxSpeed = 400.0f;

	// Defualt constructor
	Bullet() : GameObject() {}

	// Constructors
	Bullet(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject(pos, ori, textID, siz) {};
	Bullet(GameObject2D* object) : GameObject(object) {}
	
	// Functions
	void makeNew(GameObject object);
	bool deleteOffScreen(float viewWidth, float viewHeight);
	void makeNew(Bullet object);
};