#pragma once
#include "GameObject.h"

#ifndef ANIMATION_H_
#define ANIMATION_H_

class animation : public GameObject
{
private:
	// Variables
	int* textureIDs;
	float frameDelay = 0.02f;
	float timer = 0.0f;
	int curentFrame = 0;
	int totalFrames = 0;
	bool playing = false;

public:
	// Default constructor
	animation() : GameObject() {
		this->textureIDs = nullptr;
		totalFrames = 0;
	}

	// Constructor
	animation(float ori, int* textureIDs, int totalFrames, glm::vec2 siz) : GameObject(glm::vec2(1000.0f,1000.0f), ori, textureIDs[0], siz) {
		this->textureIDs = textureIDs;
		this->totalFrames = totalFrames;
	};

	// Functions
	void makeNew(animation object);
	void updateAnim(double tDelta, glm::vec2 firePos, float ori);
	void playAnim(glm::vec2 pos, float ori, double tDelta);
};
#endif
