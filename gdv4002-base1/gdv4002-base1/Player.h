#pragma once

#include "GameObject.h"
#include "GraphicsCore.h"
#include <glm/glm.hpp>
class Player : public GameObject
{
public:
	bool shotSwap = false;

	Player(glm::vec2 pos, float ori, int textID, glm::vec2 siz) : GameObject(pos, ori, textID, siz) {};
	Player(GameObject2D* object) : GameObject(object) {}
	GameObject shoot(double tDelta, float speed, int texture, glm::vec2 size);
	
};