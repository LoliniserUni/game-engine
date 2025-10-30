#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class Astroid : public GameObject
{
public:
	float rotSpeed;
	// 0 for big, 1 for medium, 2 for small
	int type;

	Astroid(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float rot, int type) : GameObject(pos, ori, textID, siz) {
		rotSpeed = rot;
		this->type = type;
	};
	Astroid(GameObject2D* object) : GameObject(object) {}
	Astroid() : GameObject() {}

	void makeNew(Astroid object);
	void updateVel(double tDelta);

	void turnLeft(double tDelta);

};