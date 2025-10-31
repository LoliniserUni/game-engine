#include "Player.h"

GameObject Player::shoot(double tDelta, float speed, int texture, glm::vec2 size, animation* lGun, animation* rGun) {
	float fX = 5 * cos(orientation);
	float fY = 5 * sin(orientation);

	// left right offset
	if (shotSwap) {
		shotSwap = false;
		fX += (2 * cos(orientation + 90 * 180 / PI)) + position.x;
		fY += (2 * sin(orientation + 90 * 180 / PI)) + position.y;

		lGun->playAnim(glm::vec2(fX, fY), orientation, tDelta);
	}
	else {
		shotSwap = true;
		fX += (2 * cos(orientation - 90 * 180 / PI)) + position.x;
		fY += (2 * sin(orientation - 90 * 180 / PI)) + position.y;

		rGun->playAnim(glm::vec2(fX, fY), orientation, tDelta);
	}

	glm::vec2 newPos = glm::vec2(fX,fY);
	float ori = orientation;

	GameObject bullet = GameObject(newPos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	return bullet;
}

void Player::setFullHealth() {
	health = 4;
	healthBar->textureID = healthTextures[health];
}
void Player::addHealth() {
	if (health < 4) {
		health++;
		healthBar->textureID = healthTextures[health];
	}
}

bool Player::reduceHealth() {
	if (hasShield) {
		hasShield = false;
		healthBar->textureID = healthTextures[health];
	}
	else {
		health--;
	}
	
	if (health < 1) {
		healthBar->textureID = healthTextures[0];
		return true;
	}
	else {
		healthBar->textureID = healthTextures[health];
		return false;
	}
}

void Player::addSheild() {
	healthBar->textureID = healthTextures[5];
	hasShield = true;
}