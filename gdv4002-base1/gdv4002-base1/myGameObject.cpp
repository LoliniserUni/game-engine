#include "myGameObject.h"


myGameObject::myGameObject() {
}
myGameObject::myGameObject(GameObject2D* object) {
	objectRef = object;
	cSpeed = 0.0f;
	cRotVel = 0.0f;
	maxSpeed = 2.0f;
	prevDir = 0.0f;
	cDir = 0.0f;
}
void myGameObject::turnLeft(double tDelta) {
	cRotVel = maxRot;

	objectRef->orientation = objectRef->orientation + (cRotVel * tDelta);
}
void myGameObject::turnRight(double tDelta) {
	cRotVel = maxRot * -1.0;

	objectRef->orientation = objectRef->orientation + (cRotVel * tDelta);
}
void myGameObject::addVelocity(glm::vec2 dir, float mag) {
	glm::vec2 accel = dir * mag;
	velocity += accel;

	if (velocity.length() > maxSpeed) {
		velocity = glm::normalize(velocity) * maxSpeed;
	}
}
void myGameObject::shoot(double tDelta) {
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
