#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include "animation.h"
#include <glm/glm.hpp>
class Player : public GameObject
{
public:
	bool shotSwap = false;
	int health = 4;
	bool hasShield = false;
	GameObject2D* healthBar;
	int* healthTextures;

	Player(glm::vec2 pos, float ori, int textID, glm::vec2 siz, GameObject2D* healthBar, int* healthTextures) : GameObject(pos, ori, textID, siz) {
		this->healthBar = healthBar;
		this->healthTextures = healthTextures;
	};
	Player(GameObject2D* object) : GameObject(object) {}
	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size, animation* lGun, animation* rGun);

	void setFullHealth();

	void addHealth();

	void addSheild();

	bool reduceHealth();
};