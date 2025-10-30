#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class Bullet : public GameObject
{
public:
	bool shotSwap = false;
	float maxSpeed = 400.0f;
	const float FIXED_LIFETIME = 2.0f;
	float lifeTime = 2.0f;

	Bullet(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject(pos, ori, textID, siz) {};
	Bullet(GameObject2D* object) : GameObject(object) {}
	Bullet() : GameObject() {}
	bool reduceTime(double tDelta);

	void makeNew(GameObject object);

	bool deleteOffScreen(float viewWidth, float viewHeight);

	void makeNew(Bullet object);
};