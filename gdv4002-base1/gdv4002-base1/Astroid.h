#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class Astroid : public GameObject
{
public:
	float rot;
	// 0 for big, 1 for medium, 2 for small
	int type;

	int hits;

	Astroid(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float rot, int type) : GameObject(pos, ori, textID, siz) {
		this->rot = rot;
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
	Astroid() : GameObject() {}

	bool addHit();
	void makeNew(Astroid object);
	void updateVel(double tDelta);

	void turnLeft(double tDelta);

};