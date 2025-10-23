#pragma once

#include "GameObject2D.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class myGameObject
{
public:
	GameObject2D* objectRef;

	float prevDir;
	float cDir;

	const float PI = 3.141593f;

	bool isSpinning = false;
	float cRotVel;
	float rotAccel = 30.0f;
	float maxRot = 10.0f;

	float cSpeed;
	float maxSpeed = 50.0f;
	float forwardAccel = 15.0f;
	float backwardsAccel = 25.0f;
	float driftLoss = 1.0f * 180 / PI;

	float newX, newY;

	float cVelOrientation;

	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);

	const float rotSpeed = glm::radians(360.0f);

	myGameObject();
	myGameObject(GameObject2D* object);
	void turnLeft(double tDelta);
	void turnRight(double tDelta);
	void addVelocity(glm::vec2 dir, float mag);
	void shoot(double tDelta);
	void updateVel(double tDelta);
	glm::vec2 getForwardVector();
	glm::vec2 getPosition();
	void keepOnScreen(float, float);
};