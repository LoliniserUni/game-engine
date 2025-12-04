#include "Astroid.h"
// Constructors
Astroid::Astroid(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float rotSpeed, int type) : GameObject(pos, ori, textID, siz) {
	this->rotSpeed = rotSpeed;
	this->type = type;
	maxSpeed = 20.0f;

	switch (this->type) {
	case 0:
		mass = 1.5f;
		hits = 10;
		break;
	case 1:
		mass = 1.0f;
		hits = 5;
		break;
	case 2:
		mass = 0.5f;
		hits = 2;
		break;
	default:
		mass = 1;
		hits = 2;
		break;
	}

	velocity = glm::vec2(0, 0);
};
Astroid::Astroid(GameObject2D* object) : GameObject(object) {
	type = 0;
	hits = 0;
	maxSpeed = 20.0f;
	mass = 100.0f;
};

// Functions
void Astroid::makeNew(Astroid object){
	// Set all members to passed objects values
 	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	velocity = object.velocity;
	rotSpeed = object.rotSpeed;
	type = object.type;
	hits = object.hits;

	mass = object.getMass();
	checkSize = object.checkSize;
	maxSpeed = 20.0f;
}


void Astroid::updateVel(double tDelta) {
	// Update the rotation
	rotate(tDelta);

	// Update the position
	GameObject::updateVel(tDelta);

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