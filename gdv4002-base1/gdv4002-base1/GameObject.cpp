#include "GameObject.h"


GameObject::GameObject() {
}


GameObject::GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz) {
	position = pos;
	orientation = ori;
	size = siz;
	textureID = textID;
}

GameObject::GameObject(GameObject2D* object) {
	position = object->position;
	orientation = object->orientation;
	size = object->size;
	textureID = object->textureID;
}
void GameObject::turnLeft(double tDelta) {

	orientation = orientation + (rotSpeed * tDelta);
	
}
void GameObject::turnRight(double tDelta) {

	orientation = orientation + (-rotSpeed * tDelta);
}
void GameObject::addVelocity(glm::vec2 dir, float mag, double tDelta) {
	glm::vec2 accel = dir * (float)tDelta * mag;
	velocity += accel;

	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity);
		velocity *= maxSpeed;

	}
}

bool GameObject::checkColl(GameObject object) {
	float bx = object.getPosition().x;
	float by = object.getPosition().y;

	float ax = getPosition().x;
	float ay = getPosition().y;

	float xDif = abs(bx - ax);
	float yDif = abs(by - ay);

	return (xDif < size.x / 2.0f && yDif < size.y / 2.0f);
}
void GameObject::setVelocity(glm::vec2 dir, float speed) {
	velocity = dir * speed;
}
void GameObject::updateVel(double tDelta) {


	position += velocity * (float)tDelta;

}

void GameObject::makeNew(GameObject object) {
	position = object.position;
	orientation = object.orientation;
	size = object.size;
	textureID = object.textureID;
}
glm::vec2 GameObject::getForwardVector() {
	float xComp = cos(orientation);
	float yComp = sin(orientation);
	glm::vec2 forwardVec = glm::vec2(xComp, yComp);

	return forwardVec;
}

glm::vec2 GameObject::getPosition() {
	return position;
}

void GameObject::keepOnScreen(float viewWidth, float viewHeight, float Buffer) {
	glm::vec2 pos = getPosition();

	viewHeight += Buffer;
	viewWidth += Buffer;
	
	if (pos.x > viewWidth) {
		position.x = -viewWidth;
	}
	else {
		if (pos.x < -viewWidth) {
			position.x = viewWidth;
		}
		else {
			// do nothing.
		}
	}
	if (pos.y > viewHeight) {
		position.y = -viewHeight;
	}
	else {
		if (pos.y < -viewHeight) {
			position.y = viewHeight;
		}
		else {
			//do nothing.
		}
	}

	/*if (pos.x > -viewWidth && pos.x < viewWidth) {
		//do nothing.
	}
	else {
		position.x = -position.x - Buffer;
	}
	if (pos.y > -viewHeight && pos.y < viewHeight) {
		//do nothing.
	}
	else {
		position.y = -1 - Buffer;
	}*/
}