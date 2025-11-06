#include "Bullet.h"
// constructor
Bullet::Bullet(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject(pos, ori, textID, siz) {};
Bullet::Bullet(GameObject2D* object) : GameObject(object) {}

//Function
void Bullet::makeNew(GameObject object) {
	// Asign passed variables to the bullet object
	position = object.getPos();
	orientation = object.getOri();
	size = object.getSize();
	textureID = object.getTexture();
}

void Bullet::makeNew(Bullet object) {
	// Set all variables to the passed objects variables
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	velocity = object.velocity;
}

bool Bullet::deleteOffScreen(float viewWidth, float viewHeight) {
	// Get the current position of the bullet
	glm::vec2 pos = position;

	// Buffer added to the size
	viewHeight += this->size.y / 0.2f;
	viewWidth += this->size.x / 0.2f;


	if (pos.x > viewWidth) {
		// If out of bounds on the right, return true
		return true;
	}
	else {
		if (pos.x < -1.0 * viewWidth) {
			// If out of bounds on the left, return true
			return true;
		}
		else {
			// If inbounds
			// do nothing.
		}
	}
	if (pos.y > viewHeight) {
		// If out of bounds at the top, return true
		return true;
	}
	else {
		// If out of bounds at the bottom, return true
		if (pos.y < -1.0 * viewHeight) {
			return true;
		}
		else {
			// If inbounds
			//do nothing.
		}
	}

	// Return false if inbounds.
	return false;
	
}

