#pragma once
#include "GameObject.h"
#include "GraphicsCore.h"
#include "Animation.h"
#include <glm/glm.hpp>

#ifndef PLAYER_H_
#define PLAYER_H_

class Player : public GameObject
{
private:
	// Variables
	bool shotSwap = false;
	int health = 4;
	bool hasShield = false;
	GameObject2D* healthBar;
	GameObject2D* shield;
	int* healthTextures;

public:
	// Constructors
	Player(glm::vec2 pos, float ori, int textID, glm::vec2 siz, GameObject2D* healthBar, int* healthTextures, GameObject2D* shieldBubble);
	Player(GameObject2D* object);

	// Functions
	void update(double tDelta);
	GameObject2D* getShield();
	GameObject2D* getHB();
	void resetVel();
	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size, Animation* lGun, Animation* rGun);
	void turnLeft(double tDelta);
	void turnRight(double tDelta);
	void addVelocity(glm::vec2 dir, float mag, double tDelta);
	void setFullHealth();
	void addHealth();
	void addSheild();
	bool reduceHealth();
};
#endif