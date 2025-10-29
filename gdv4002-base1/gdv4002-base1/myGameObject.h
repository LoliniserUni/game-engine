#pragma once

#include "GameObject2D.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class myGameObject : public GameObject2D
{
public:
	float cDir;

	const float PI = 3.141593f;

	float rotAccel = 30.0f;
	float maxRot = 10.0f;

	float maxSpeed = 200.0f;
	float forwardAccel = 15.0f;
	float backwardsAccel = 25.0f;
	float driftLoss = 1.0f * 180 / PI;

	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);

	const float rotSpeed = glm::radians(360.0f);

	myGameObject();
	myGameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz);
	myGameObject(GameObject2D* object);
	void turnLeft(double tDelta);
	void turnRight(double tDelta);
	void addVelocity(glm::vec2 dir, float mag, double tDelta);
	void updateVel(double tDelta);
	glm::vec2 getForwardVector();
	glm::vec2 getPosition();
	void keepOnScreen(float, float);
	void setVelocity(glm::vec2 dir, float speed);
	myGameObject shoot(double tDelta, float speed, int texture, glm::vec2 size);
	void makeNew(myGameObject object);
};