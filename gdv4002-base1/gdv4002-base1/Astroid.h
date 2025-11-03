#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class Astroid : public GameObject
{
public:
	// Variables
	int type;
	int hits;

	// Default constructor
	Astroid() : GameObject() {}

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
	Astroid(GameObject2D* object) : GameObject(object) {}
	
	// Functions
	bool addHit();
	void makeNew(Astroid object);
	void updateVel(double tDelta);
	void rotate(double tDelta);

};