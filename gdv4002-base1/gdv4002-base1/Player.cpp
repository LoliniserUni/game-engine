#include "Player.h"
// Constructors
Player::Player(glm::vec2 pos, float ori, int textID, glm::vec2 siz, GameObject2D* healthBar, int* healthTextures, GameObject2D* shieldBubble) : GameObject(pos, ori, textID, siz) {
	this->healthBar = healthBar;
	this->healthTextures = healthTextures;
	shield = shieldBubble;
};

Player::Player(GameObject2D* object) : GameObject(object) {
	healthBar = new GameObject2D();
	healthTextures = nullptr;
	shield = nullptr;
}

void Player::update(double tDelta) {
	updateVel(tDelta);
	if (hasShield) shield->setPos(position);
}
GameObject2D* Player::getHB() {
	return healthBar;
}

GameObject2D* Player::getShield() {
	return shield;
}

void Player::resetVel() {
	velocity = glm::vec2(0, 0);
}
void Player::turnLeft(double tDelta) {
	// Add the rotation speed * time delta to the orientation 
	orientation = orientation + (rotSpeed * (float) tDelta);

}
void Player::turnRight(double tDelta) {
	// subtract the rotation speed * time delta to the orientation 
	orientation = orientation + (-rotSpeed * (float) tDelta);
}

void Player::addVelocity(glm::vec2 dir, float mag, double tDelta) {
	// Get the acceleartion in the applied direction, and * by the magnitude and the time delta
	glm::vec2 accel = dir * (float)tDelta * mag;

	// Add the acceleration to the velocity
	velocity += accel;

	// If the velocity is over the max speed
	if (glm::length(velocity) > maxSpeed) {

		// Normalize the velocity and * by the max speed
		velocity = glm::normalize(velocity);
		velocity *= maxSpeed;

	}
}

GameObject Player::shoot(double tDelta, float speed, int texture, glm::vec2 size, Animation* lGun, Animation* rGun) {

	// Get the current position, and offset it forwards
	float fX = 5 * cos(orientation) + position.x;
	float fY = 5 * sin(orientation) + position.y;

	// Either offset to the left or to the right, depending on if shotswap is true or false
	if (shotSwap) {
		shotSwap = false;
		fX += (2 * cos(orientation + 90 * 180 / PI));
		fY += (2 * sin(orientation + 90 * 180 / PI));

		// Play the left gun Animation at this position
		lGun->playAnim(glm::vec2(fX, fY), orientation, tDelta);
	}
	else {
		shotSwap = true;
		fX += (2 * cos(orientation - 90 * 180 / PI));
		fY += (2 * sin(orientation - 90 * 180 / PI));

		// Play the right gun Animation at this position
		rGun->playAnim(glm::vec2(fX, fY), orientation, tDelta);
	}

	// Set the new position and get the orientation 
	glm::vec2 newPos = glm::vec2(fX,fY);
	float ori = orientation;

	// Create a bullet, and set its velocity
	GameObject bullet = GameObject(newPos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	// Return the Bullet
	return bullet;
}

void Player::setFullHealth() {
	// Set the health bar to full, and render the health bars correct texture
	health = 4;
	healthBar->setTexture(healthTextures[health]);
}
void Player::addHealth() {
	// Check that the player isnt at max health
	if (health < 4) {
		// If not at max health, add health and render the new health bar
		health++;
		healthBar->setTexture(healthTextures[health]);
	}
}

bool Player::reduceHealth() {
	// if the player has a sheild
	if (hasShield) {
		// remove the sheuld and set the correct health bar texture
		hasShield = false;
		healthBar->setTexture(healthTextures[health]);
		shield->setPos(glm::vec2(1000.0f,1000.0f));

		// return false
		return false;
	}
	else {
		// Remove health
		health--;
	}
	
	// If health is 0 (aka player is dead)
	if (health < 1) {
		// Render the empty health bar
		healthBar->setTexture(healthTextures[0]);

		// return true
		return true;
	}
	else {
		// Set the health bar to the correct texture
		healthBar->setTexture(healthTextures[health]);

		// return false
		return false;
	}
}

void Player::addSheild() {
	// Set the health bar etxture to the sheild texture, and set hasShield to true
	shield->setPos(position);
	hasShield = true;
}

