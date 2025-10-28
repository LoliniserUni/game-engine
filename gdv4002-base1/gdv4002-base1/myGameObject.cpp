#include "myGameObject.h"


myGameObject::myGameObject() {
}
myGameObject::myGameObject(GameObject2D* object) {
	objectRef = object;
	cDir = object->orientation;
}
void myGameObject::turnLeft(double tDelta) {
	cRotVel = maxRot;

	objectRef->orientation = objectRef->orientation + (cRotVel * tDelta);
}
void myGameObject::turnRight(double tDelta) {
	cRotVel = maxRot * -1.0;

	objectRef->orientation = objectRef->orientation + (cRotVel * tDelta);
}
void myGameObject::addVelocity(glm::vec2 dir, float mag, double tDelta) {
	glm::vec2 accel = dir * (float) tDelta * mag;
	velocity += accel;

	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity);
		velocity *= maxSpeed;
		
	}
}
void myGameObject::updateVel(double tDelta) {
	
	
	objectRef->position += velocity * (float)tDelta;

}

glm::vec2 myGameObject::getForwardVector() {
	float xComp = cos(objectRef->orientation);
	float yComp = sin(objectRef->orientation);
	glm::vec2 forwardVec = glm::vec2(xComp, yComp);

	return forwardVec;
}

glm::vec2 myGameObject::getPosition() {
	return objectRef->position;
}

void myGameObject::keepOnScreen(float viewWidth, float viewHeight) {
	glm::vec2 pos = getPosition();

	viewHeight += 5;
	viewWidth += 5;
	/*
	if (pos.x > viewWidth) {
		objectRef->position.x = -1.0 * viewWidth;
	}
	else {
		if (pos.x < -1.0 * viewWidth) {
			objectRef->position.x = viewWidth;
		}
		else {
			// do nothing.
		}
	}
	if (pos.y > viewHeight) {
		objectRef->position.y = -1.0 * viewHeight;
	}
	else {
		if (pos.y < -1.0 * viewHeight) {
			objectRef->position.y = viewHeight;
		}
		else {
			//do nothing.
		}
	}
	*/

	if (pos.x > -viewWidth && pos.x < viewWidth) {
		//do nothing.
	}
	else {
		objectRef->position.x *= -1;
	}
	if (pos.y > -viewHeight && pos.y < viewHeight) {
		//do nothing.
	}
	else {
		objectRef->position.y *= -1;
	}
}