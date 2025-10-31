#include "animation.h"

void animation::updateAnim(double tDelta, glm::vec2 firePos) {
	if (playing) {
		timer += tDelta;
		if (timer >= frameDelay) {
			timer = 0.0f;
			if (curentFrame >= totalFrames) {
				curentFrame = 0;
				playing = false;
				this->position = glm::vec2(1000.0f, 1000.0f);
				//this->textureID = textureIDs[0];
				return;
			}
			this->position = firePos;
			this->textureID = textureIDs[curentFrame];
			curentFrame++;
		}
	}
	else {
		//do nothing
	}
	
}
void animation::playAnim(glm::vec2 pos, float ori, double tDelta) {
	this->position = pos;
	this->orientation = ori;
	playing = true;

	curentFrame = 0;
	this->textureID = textureIDs[0];
}