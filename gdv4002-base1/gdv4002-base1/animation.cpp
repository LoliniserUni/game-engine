#include "animation.h"

void animation::makeNew(animation object) {

	// Set all variables to be the passed object
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

void animation::updateAnim(double tDelta, glm::vec2 firePos, float ori) {

	// If the animation is playing
	if (playing) {

		// Increment the timer
		timer += (float) tDelta;

		// Check if its time to play the next frame
		if (timer >= frameDelay) {

			// Reset the timer
			timer = 0.0f;

			// If current frame is the final frame
			if (curentFrame >= totalFrames) {

				// Reset to the starting frame
				curentFrame = 0;

				// Set playing to false
				playing = false;

				// Move the animation out of bounds
				this->position = glm::vec2(1000.0f, 1000.0f);

				//No need to set the active frame to the first, as the animation is off screen
				
				//Exit
				return;
			}
			// Move the animation to the current position
			this->position = firePos;

			// Rotate the orientation to the current orientation
			this->orientation = ori;

			// Set the texture
			this->textureID = textureIDs[curentFrame];

			// Go to next frame
			curentFrame++;
		}
	}
	else {
		//do nothing
	}
}
void animation::playAnim(glm::vec2 pos, float ori, double tDelta) {

	// Bring the animation to the current position
	this->position = pos;

	// Set orientation to the current orientation
	this->orientation = ori;

	// Set playing to true
	playing = true;

	// Reset current frame and texture
	curentFrame = 0;
	this->textureID = textureIDs[0];
}