#pragma once
#include "GameObject.h"

#ifndef Animation_H_
#define Animation_H_

class Animation : public GameObject
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
	Animation();

	// Constructor
	Animation(float ori, int* textureIDs, int totalFrames, glm::vec2 siz);

	// Functions
	void makeNew(Animation object);
	void updateAnim(double tDelta, glm::vec2 firePos, float ori);
	void playAnim(glm::vec2 pos, float ori, double tDelta);
};
#endif
