#include "Bullet.h"

bool Bullet::reduceTime(double tDelta) {
	lifeTime -= (float)tDelta;
	return lifeTime <= 0.0f;
}

void Bullet::makeNew(GameObject object) {
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	lifeTime = FIXED_LIFETIME;
}

bool Bullet::deleteOffScreen(float viewWidth, float viewHeight) {
	glm::vec2 pos = getPosition();

	viewHeight += 10;
	viewWidth += 10;


	if (pos.x > viewWidth) {
		return true;
	}
	else {
		if (pos.x < -1.0 * viewWidth) {
			return true;
		}
		else {
			// do nothing.
		}
	}
	if (pos.y > viewHeight) {
		return true;
	}
	else {
		if (pos.y < -1.0 * viewHeight) {
			return true;
		}
		else {
			//do nothing.
		}
	}
	return false;
	
}

void Bullet::makeNew(Bullet object) {
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	lifeTime = FIXED_LIFETIME;
	velocity = object.velocity;
}