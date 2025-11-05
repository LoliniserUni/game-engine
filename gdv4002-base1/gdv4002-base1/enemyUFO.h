#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include "Animation.h"
#include <glm/glm.hpp>

#ifndef ENEMYUFO_H_
#define ENEMYUFO_H_


class EnemyUFO : public GameObject
{
private:
	// Variables
	int health = 15;
	float ufoShotTimer = 0.0f;
	Animation* flare;

public:
	// Default constructor
	EnemyUFO() : GameObject() {
		this->flare = new Animation();
	};

	// Constructors
	EnemyUFO(glm::vec2 pos, float ori, int textID, glm::vec2 siz, Animation* shootFlare);
	EnemyUFO(GameObject2D* object);
	
	Animation* getAnim();
	float getTimer();
	void setTimer(float timer);
	// Functions
	void addToTimer(double tDelta);
	void updateAnim(double tDelta, glm::vec2 firePos, float ori);
	void playAnim(glm::vec2 pos, float ori, double tDelta);
	void makeNew(EnemyUFO ufo);
	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size);
	bool reduceHealth();
};

#endif