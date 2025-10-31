#pragma once
#include "GameObject.h"
class animation : public GameObject
{
public: 
	int* textureIDs;
	float frameDelay = 0.02f;
	float timer = 0.0f;
	int curentFrame = 0;
	int totalFrames = 0;

	bool playing = false;

	animation() : GameObject() {};

	animation(float ori, int* textureIDs, int totalFrames, glm::vec2 siz) : GameObject(glm::vec2(1000.0f,1000.0f), ori, textureIDs[0], siz) {
		this->textureIDs = textureIDs;
		this->totalFrames = totalFrames;
	};

	void makeNew(animation object) {
		this->textureIDs = object.textureIDs;
		this->frameDelay = object.frameDelay;
		this->timer = 0.0f;
		this->curentFrame = 0;
		this->totalFrames = object.totalFrames;
		this->position = glm::vec2(1000.0f, 1000.0f);
		this->orientation = 0.0f;
		this->textureID = textureIDs[0];
		this->size = object.size;
	}

	void updateAnim(double tDelta, glm::vec2 firePos);
	void playAnim(glm::vec2 pos, float ori, double tDelta);
};

