#include "Astroid.h"
// Constructors
Astroid::Astroid(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float rotSpeed, int type) : GameObject(pos, ori, textID, siz) {
	this->rotSpeed = rotSpeed;
	this->type = type;

	switch (this->type) {
	case 0:
		hits = 7;
		break;
	case 1:
		hits = 3;
		break;
	case 2:
		hits = 1;
		break;
	default:
		hits = 1;
		break;
	}
};
Astroid::Astroid(GameObject2D* object) : GameObject(object) {
	type = 0;
	hits = 0;
};

// Functions
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
	orientation = orientation + (rotSpeed * (float) tDelta);
}

bool Astroid::addHit() {
	// subtract 1 hit
	hits--;

	// return true if the astroid is broken, false if its still alive
	return hits < 1;
}