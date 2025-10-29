#include "Player.h"

GameObject Player::shoot(double tDelta, float speed, int texture, glm::vec2 size) {
	float nX, nY;
	if (shotSwap) {
		shotSwap = false;
		nX = 2 * cos(orientation + 90 * 180 / PI);
		nY = 2 * sin(orientation + 90 * 180 / PI);
	}
	else {
		shotSwap = true;
		nX = 2 * cos(orientation - 90 * 180/PI);
		nY = 2 * sin(orientation - 90 * 180 / PI);
	}
	glm::vec2 newPos = glm::vec2(nX+position.x,nY+position.y);
	float ori = orientation;

	GameObject bullet = GameObject(newPos, ori, texture, size);
	bullet.setVelocity(bullet.getForwardVector(), speed);

	return bullet;
}