#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include "animation.h"
#include <glm/glm.hpp>

#ifndef ENEMYUFO_H_
#define ENEMYUFO_H_


class enemyUFO : public GameObject
{
private:
	// Variables
	int health = 15;
	float ufoShotTimer = 0.0f;
	animation* flare;

public:
	// Default constructor
	enemyUFO() : GameObject() {
		this->flare = new animation();
	};

	// Constructors
	enemyUFO(glm::vec2 pos, float ori, int textID, glm::vec2 siz, animation* shootFlare) : GameObject(pos, ori, textID, siz) {
		this->flare = shootFlare;
	};
	enemyUFO(GameObject2D* object) : GameObject(object) {
		this->flare = new animation();
	};
	
	animation* getAnim();
	float getTimer();
	void setTimer(float timer);
	// Functions
	void addToTimer(double tDelta);
	void updateAnim(double tDelta, glm::vec2 firePos, float ori);
	void playAnim(glm::vec2 pos, float ori, double tDelta);
	void makeNew(enemyUFO ufo);
	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size);
	bool reduceHealth();
};

#endif