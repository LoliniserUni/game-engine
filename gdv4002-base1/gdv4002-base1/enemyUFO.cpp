#include "enemyUFO.h"

GameObject enemyUFO::shoot(double tDelta, float speed, int texture, glm::vec2 size) {
	//float fX = 5 * cos(orientation - glm::radians(180.0f));
	//float fY = 5 * sin(orientation - glm::radians(180.0f));

	float fX = position.x;
	float fY = position.y - 2.5f;

	glm::vec2 newPos = glm::vec2(fX, fY);
	float ori = orientation - glm::radians(90.0f);

	GameObject bullet = GameObject(newPos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	return bullet;
}

bool enemyUFO::reduceHealth() {
	if (health < 1) {
		return true;
	}
	else {
		health--;
		return false;
	}
}

void enemyUFO::makeNew(enemyUFO ufo) {
	this->position = ufo.position;
	this->health = ufo.health;
	this->velocity = ufo.velocity;
	this->orientation = ufo.orientation;
	this->textureID = ufo.textureID;
	this->size = ufo.size;
}