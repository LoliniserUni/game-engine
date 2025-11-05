#pragma once
#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>

#ifndef ASTROID_H_
#define ASTROID_H_

class Astroid : public GameObject
{
private:
	// Variables
	int type;
	int hits;

public:

	// Default constructor
	Astroid() : GameObject() {
		type = 0;
		hits = 0;
	}

	// Constructors
	Astroid(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float rotSpeed, int type);
	Astroid(GameObject2D* object);
	
	// Functions
	bool addHit();
	void makeNew(Astroid object);
	void updateVel(double tDelta);
	void rotate(double tDelta);

};
#endif