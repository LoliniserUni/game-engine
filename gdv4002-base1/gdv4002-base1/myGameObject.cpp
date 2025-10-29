#include "myGameObject.h"


myGameObject::myGameObject() {
}


myGameObject::myGameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz) {
	position = pos;
	orientation = ori;
	size = siz;
	textureID = textID;
}

myGameObject::myGameObject(GameObject2D* object) {
	position = object->position;
	orientation = object->orientation;
	size = object->size;
	textureID = object->textureID;
}
void myGameObject::turnLeft(double tDelta) {

	orientation = orientation + (maxRot * tDelta);
}
void myGameObject::turnRight(double tDelta) {

	orientation = orientation + (-maxRot * tDelta);
}
void myGameObject::addVelocity(glm::vec2 dir, float mag, double tDelta) {
	glm::vec2 accel = dir * (float) tDelta * mag;
	velocity += accel;

	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity);
		velocity *= maxSpeed;
		
	}
}

void myGameObject::setVelocity(glm::vec2 dir, float speed) {
	velocity = dir * speed;
}
void myGameObject::updateVel(double tDelta) {
	
	
	position += velocity * (float)tDelta;

}

void myGameObject::makeNew(myGameObject object) {
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
}
glm::vec2 myGameObject::getForwardVector() {
	float xComp = cos(orientation);
	float yComp = sin(orientation);
	glm::vec2 forwardVec = glm::vec2(xComp, yComp);

	return forwardVec;
}

glm::vec2 myGameObject::getPosition() {
	return position;
}

myGameObject myGameObject::shoot(double tDelta, float speed, int texture, glm::vec2 size) {
	glm::vec2 pos = position;
	float ori = orientation;
	
	myGameObject bullet = myGameObject(pos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	return bullet;
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
		position.x *= -1;
	}
	if (pos.y > -viewHeight && pos.y < viewHeight) {
		//do nothing.
	}
	else {
		position.y *= -1;
	}
}