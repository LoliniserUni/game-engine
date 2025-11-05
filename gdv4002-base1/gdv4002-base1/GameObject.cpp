#include "GameObject.h"
//Constructors
GameObject::GameObject(GameObject2D* object) : GameObject2D(object->getPos(), object->getOri(), object->getSize(), object->getTexture()) {}
GameObject::GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject2D(pos, ori, siz, textID) {};

//Functions
bool GameObject::checkColl(GameObject object) {
	// Get passed objects position
	float bx = object.position.x;
	float by = object.position.y;

	// Get current position
	float ax = position.x;
	float ay = position.y;

	// Get the distance between the 2 2objects
	float xDif = abs(bx - ax);
	float yDif = abs(by - ay);

	// Return true if the distance between the 2 points is smaller than this objects size (ie, the passed objects centre is within this objects size)
	return (xDif < size.x / 2.0f && yDif < size.y / 2.0f);
}

void GameObject::setVelocity(glm::vec2 dir, float speed) {
	// Set the velocity
	velocity = dir * speed;
}
void GameObject::updateVel(double tDelta) {
	// Update position based on the velocity * the time delta
	position += velocity * (float)tDelta;

}

void GameObject::makeNew(GameObject object) {
	// Set all variables to the passed objects values
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
}

glm::vec2 GameObject::getForwardVector() {
	
	// Get the x and y coordinates of the forwards direction in the unit circle
	float xComp = cos(orientation);
	float yComp = sin(orientation);

	// Return this forward vector
	glm::vec2 forwardVec = glm::vec2(xComp, yComp);
	return forwardVec;
}

void GameObject::keepOnScreen(float viewWidth, float viewHeight) {
	// Get the current position
	glm::vec2 pos = this->position;

	// Offset the width and height by half the objects dimentions
	viewHeight += this->size.y / 2.0f;
	viewWidth += this->size.x / 2.0f;
	
	if (pos.x > viewWidth) {
		// if position is out of bounds on the right, teleport to the left
		position.x = -viewWidth;
	}
	else {
		if (pos.x < -viewWidth) {
			// if position is out of bounds on the left, teleport to the right
			position.x = viewWidth;
		}
		else {
			// if position is in bounds
			// do nothing.
		}
	}
	if (pos.y > viewHeight) {
		// if position is out of bounds on the top, teleport to the bottom
		position.y = -viewHeight;
	}
	else {
		if (pos.y < -viewHeight) {
			// if position is out of bounds on the bottom, teleport to the top
			position.y = viewHeight;
		}
		else {
			// if position is in bounds
			//do nothing.
		}
	}
}