#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include "animation.h"
#include <glm/glm.hpp>
class enemyUFO : public GameObject
{
public:
	bool shotSwap = false;
	int health = 15;
	float ufoShotTimer = 0.0f;

	enemyUFO() {};
	enemyUFO(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject(pos, ori, textID, siz) {};

	enemyUFO(GameObject2D* object) : GameObject(object) {}

	void makeNew(enemyUFO ufo);

	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size);

	bool reduceHealth();
};