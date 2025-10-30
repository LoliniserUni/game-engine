#include "Astroid.h"

void Astroid::makeNew(Astroid object) {
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	velocity = object.velocity;
	rot = object.rot;
	type = object.type;
}


void Astroid::updateVel(double tDelta) {

	turnLeft(tDelta);
	position += velocity * (float)tDelta;

}

void Astroid::turnLeft(double tDelta) {
	orientation = orientation + (rot * tDelta);
}