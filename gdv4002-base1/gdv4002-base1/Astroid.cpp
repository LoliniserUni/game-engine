#include "Astroid.h"

void Astroid::makeNew(Astroid object) {
	// Set all members to passed objects values
 	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	velocity = object.velocity;
	rotSpeed = object.rotSpeed;
	type = object.type;
	hits = object.hits;
}


void Astroid::updateVel(double tDelta) {
	// Update the rotation
	rotate(tDelta);

	// Update the position
	position += velocity * (float)tDelta;

}

void Astroid::rotate(double tDelta) {
	// Add the rotation speed to the orientation
	orientation = orientation + (rotSpeed * tDelta);
}

bool Astroid::addHit() {
	// subtract 1 hit
	hits--;

	// return true if the astroid is broken, false if its still alive
	return hits < 1;
}