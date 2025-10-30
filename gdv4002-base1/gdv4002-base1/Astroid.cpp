#include "Astroid.h"

void Astroid::makeNew(Astroid object) {
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	velocity = object.velocity;
}


void Astroid::updateVel(double tDelta) {

	turnLeft(tDelta);
	position += velocity * (float)tDelta;

}

void Astroid::turnLeft(double tDelta) {
	orientation = orientation + (rotSpeed * tDelta);
}