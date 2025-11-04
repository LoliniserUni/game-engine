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
	Astroid(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float rotSpeed, int type) : GameObject(pos, ori, textID, siz) {
		this->rotSpeed = rotSpeed;
		this->type = type;

		switch (this->type) {
		case 0:
			hits = 7;
			break;
		case 1:
			hits = 3;
			break;
		case 2:
			hits = 1;
			break;
		default:
			hits = 1;
			break;
		}
	};
	Astroid(GameObject2D* object) : GameObject(object) {
		type = 0;
		hits = 0;
	};
	
	// Functions
	bool addHit();
	void makeNew(Astroid object);
	void updateVel(double tDelta);
	void rotate(double tDelta);

};
#endif