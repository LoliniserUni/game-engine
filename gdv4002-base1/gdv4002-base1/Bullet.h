#pragma once
#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
#ifndef BULLET_H_
#define BULLET_H_

class Bullet : public GameObject
{
private:
	// Variables
	float maxSpeed = 400.0f;

public:
	// Defualt constructor
	Bullet() : GameObject() {}

	// Constructors
	Bullet(glm::vec2 pos, float ori, int textID, glm::vec2 siz);
	Bullet(GameObject2D* object);
	
	// Functions
	void makeNew(GameObject object);
	bool deleteOffScreen(float viewWidth, float viewHeight);
	void makeNew(Bullet object);
};

#endif