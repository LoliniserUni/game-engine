#include "enemyUFO.h"

void enemyUFO::makeNew(enemyUFO ufo) {
	// Set the ufos variables to the passed ufos values
	this->position = ufo.position;
	this->health = ufo.health;
	this->velocity = ufo.velocity;
	this->orientation = ufo.orientation;
	this->textureID = ufo.textureID;
	this->size = ufo.size;
	this->flare = ufo.flare;
}

GameObject enemyUFO::shoot(double tDelta, float speed, int texture, glm::vec2 size) {

	// Get the current position, and offset it down
	float fX = position.x;
	float fY = position.y - 2.5f;

	// Set position and orientation
	glm::vec2 newPos = glm::vec2(fX, fY);
	float ori = orientation - glm::radians(90.0f);

	// Create the new bullet, and set its velocity
	GameObject bullet = GameObject(newPos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	// Play the muzzle flash animation
	flare->playAnim(newPos, ori,tDelta);

	// Return the bullet
	return bullet;
}

bool enemyUFO::reduceHealth() {
	// If the UFO is dead
	if (health < 1) {
		// return true
		return true;
	}
	else {
		// Subtract 1 from health and return false
		health--;
		return false;
	}
}