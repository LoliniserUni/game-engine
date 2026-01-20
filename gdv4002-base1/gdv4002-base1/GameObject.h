#include "GameObject2D.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_


const float PI = 3.141593f;

class GameObject : public GameObject2D
{
protected:
	// Variables
	float checkSize;
	int maxSpeed = 200;
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	float rotSpeed = glm::radians(420.0f);
	float mass = 1.0f;

public:
	// Default constructor
	GameObject();

	// Constructors
	GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz);

	GameObject(glm::vec2 pos, float ori, int textID, glm::vec2 siz, float mass);
	GameObject(GameObject2D* object);

	glm::vec2 getVel();

	// Functions
	float getCheckSize();
	void updateVel(double tDelta);
	glm::vec2 getForwardVector();
	void keepOnScreen(float height, float width);
	void setVelocity(glm::vec2 dir, float speed);
	void setVelocity(glm::vec2 vel);
	void addVleocity(glm::vec2 dir, float mag, double tDelta);
	float getMass();
	void makeNew(GameObject object);
	bool checkColl(GameObject* object, float tDelta);
	void setMass(float mass);
};

#endif