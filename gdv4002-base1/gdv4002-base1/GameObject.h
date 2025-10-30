#pragma once

#include "GameObject2D.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class GameObject : public GameObject2D
{
public:
	const float PI = 3.141593f;
	float maxSpeed = 200.0f;
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	const float rotSpeed = glm::radians(420.0f);

	GameObject();
	GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz);
	GameObject(GameObject2D* object);
	void turnLeft(double tDelta);
	void turnRight(double tDelta);
	void addVelocity(glm::vec2 dir, float mag, double tDelta);
	void updateVel(double tDelta);
	glm::vec2 getForwardVector();
	glm::vec2 getPosition();
	void keepOnScreen(float, float, float buffer);
	void setVelocity(glm::vec2 dir, float speed);
	void makeNew(GameObject object);
};