#include "GameObject.h"
//Constructors
GameObject::GameObject() : GameObject2D() {
	checkSize = 0.0f;

	velocity = glm::vec2(0, 0);
}

GameObject::GameObject(GameObject2D* object) : GameObject2D(object->getPos(), object->getOri(), object->getSize(), object->getTexture()) {
	checkSize = abs(object->getSize().x / 2.0f) * abs(object->getSize().x / 2.0f);

	velocity = glm::vec2(0, 0);
}
GameObject::GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject2D(pos, ori, siz, textID) {
	checkSize = abs(siz.x / 2.0f) * abs(siz.x / 2.0f);

	velocity = glm::vec2(0, 0);
};

GameObject::GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float mass) : GameObject(pos, ori, textID, siz) {
	this->mass = mass;

	velocity = glm::vec2(0, 0);
}
glm::vec2 GameObject::getVel() {
	return velocity;
}
float GameObject::getCheckSize() {
	return checkSize;
}

//Functions
bool GameObject::checkColl(GameObject* object, float tDelta) {

	// Get passed objects position
	float bx = object->position.x;
	float by = object->position.y;

	// Get current position
	float ax = position.x;
	float ay = position.y;

	float xDist = abs(ax - bx);
	float yDist = abs(ay - by);

	float distance = xDist * xDist + yDist * yDist;

	bool res = distance < checkSize + object->getCheckSize();

	if (res) {
		glm::vec2 impactDirection = (object->getPos() - position);
		impactDirection = glm::normalize(impactDirection);

		glm::vec2 velocityDifference = velocity - object->getVel();

		float dot = glm::dot(velocityDifference, velocityDifference);
		glm::vec2 impactOffset = object->getMass() / mass * impactDirection * dot * tDelta;
		if (glm::length(impactOffset) > 1000) {

			// Normalize the velocity and * by the max speed
			impactOffset = glm::normalize(impactOffset);
			impactOffset *= 1000;

		}

		setVelocity((getVel() - impactOffset));
		object->setVelocity((object->getVel() + impactOffset));
	}

	return res;

	// Return true if the distance between the 2 points is smaller than this objects size (ie, the passed objects centre is within this objects size)
	//return (xDif < size.x / 2.0f && yDif < size.y / 2.0f);
}

void GameObject::setMass(float mass) {
	this->mass = mass;
}
void GameObject::setVelocity(glm::vec2 dir, float speed) {
	// Set the velocity
	velocity = dir * speed;
}

void GameObject::setVelocity(glm::vec2 vel) {
	// Set the velocity
	velocity = vel;
}
void GameObject::updateVel(double tDelta) {

	// If the velocity is over the max speed
	if (glm::length(velocity) > maxSpeed) {

		// Normalize the velocity and * by the max speed
		velocity = glm::normalize(velocity);
		velocity *= maxSpeed;

	}

	// Update position based on the velocity * the time delta
	position += velocity * (float)tDelta;



}

void GameObject::addVleocity(glm::vec2 dir, float mag, double tDelta) {
	// Get the acceleartion in the applied direction, and * by the magnitude and the time delta
	glm::vec2 accel = dir * (float)tDelta * mag / mass;

	// Add the acceleration to the velocity
	velocity += accel;
}

float GameObject::getMass() {
	return mass;
}
void GameObject::makeNew(GameObject object) {
	// Set all variables to the passed objects values
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
	checkSize = object.checkSize;
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
	viewHeight += this->size.y / 2.0f -5;
	viewWidth += this->size.x / 2.0f -5;
	
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