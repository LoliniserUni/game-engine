#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include "animation.h"
#include <glm/glm.hpp>
class Player : public GameObject
{
public:
	// Variables
	bool shotSwap = false;
	int health = 4;
	bool hasShield = false;
	GameObject2D* healthBar;
	int* healthTextures;

	// Constructors
	Player(glm::vec2 pos, float ori, int textID, glm::vec2 siz, GameObject2D* healthBar, int* healthTextures) : GameObject(pos, ori, textID, siz) {
		this->healthBar = healthBar;
		this->healthTextures = healthTextures;
	};
	Player(GameObject2D* object) : GameObject(object) {}

	// Functions
	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size, animation* lGun, animation* rGun);
	void turnLeft(double tDelta);
	void turnRight(double tDelta);
	void addVelocity(glm::vec2 dir, float mag, double tDelta);
	void setFullHealth();
	void addHealth();
	void addSheild();
	bool reduceHealth();
};