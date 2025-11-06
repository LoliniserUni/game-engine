#include "EnemyUFO.h"
//Constructors
EnemyUFO::EnemyUFO(glm::vec2 pos, float ori, int textID, glm::vec2 siz, Animation* shootFlare) : GameObject(pos, ori, textID, siz) {
	this->flare = shootFlare;
}
EnemyUFO::EnemyUFO(GameObject2D* object) : GameObject(object) {
	this->flare = new Animation();
}

// Functions
Animation* EnemyUFO::getAnim() {
	return flare;
}

float EnemyUFO::getTimer() { 
	return ufoShotTimer; 
}

void EnemyUFO::setTimer(float timer) {
	ufoShotTimer = timer;
}

void EnemyUFO::addToTimer(double tDelta) {
	ufoShotTimer += (float) tDelta;
}

void EnemyUFO::updateAnim(double tDelta, glm::vec2 firePos, float ori) {
	flare->updateAnim(tDelta, firePos, ori);
}

void EnemyUFO::playAnim(glm::vec2 pos, float ori, double tDelta) {
	flare->playAnim(pos, ori, tDelta);
}

void EnemyUFO::makeNew(EnemyUFO ufo) {
	// Set the ufos variables to the passed ufos values
	this->position = ufo.position;
	this->health = ufo.health;
	this->velocity = ufo.velocity;
	this->orientation = ufo.orientation;
	this->textureID = ufo.textureID;
	this->size = ufo.size;
	this->flare = ufo.flare;
}

GameObject EnemyUFO::shoot(double tDelta, float speed, int texture, glm::vec2 size) {

	// Get the current position, and offset it down
	float fX = position.x;
	float fY = position.y - 2.5f;

	// Set position and orientation
	glm::vec2 newPos = glm::vec2(fX, fY);
	float ori = orientation - glm::radians(90.0f);

	// Create the new bullet, and set its velocity
	GameObject bullet = GameObject(newPos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	// Play the muzzle flash Animation
	flare->playAnim(newPos, ori,tDelta);

	// Return the bullet
	return bullet;
}

bool EnemyUFO::reduceHealth() {
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