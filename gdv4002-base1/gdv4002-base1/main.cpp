#include "Engine.h"
#include "myGameObject.h"

// Function prototypes
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void playerControl(double);
void shoot(double);
void updateBullet(double);

float shootCooldownLen = 0.5f;
float shootCooldown = 0;
bool wKey, aKey, sKey, dKey,spaceKey = false;
int bulletNum = 0;

float bulletMag = 500.0;
const float PI = 3.141593f;

float forwardForce = 200.0f;

float width, height;

myGameObject* player;

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024,160.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("player",glm::vec2(10.0f,10.0f),glm::radians(270.0f),glm::vec2(10.0f,10.0f),"Resources\\Textures\\player1_ship.png",TextureProperties::NearestFilterTexture());

	myGameObject temp = myGameObject(getObject("player"));
	player = &temp;

	width = getViewplaneWidth();
	height = getViewplaneHeight();
	setKeyboardHandler(myKeyboardHandler);
	
	setUpdateFunction(myUpdateScene);
	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}
void myUpdateScene(GLFWwindow* window, double tDelta) {
	//Update Function
	
	playerControl(tDelta);
	player->keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f);
	updateBullet(tDelta);
}
void playerControl(double tDelta) {
	if (aKey) {
		player->turnLeft(tDelta);
	}
	if (dKey) {
		player->turnRight(tDelta);
	}
	if (wKey) {
		player->addVelocity(player->getForwardVector(), forwardForce, tDelta);
	}
	if (sKey) {
		player->addVelocity(player->getForwardVector(), forwardForce*-1.0, tDelta);
	}if (spaceKey) {
		shoot(tDelta);
	}

	player->updateVel(tDelta);
}

void updateBullet(double tDelta) {
	for (int x = 1; x < bulletNum; x++) {
		GameObject2D* bullet = getObject("bullet" + bulletNum);

		myGameObject bulletObject = myGameObject(bullet);
		bulletObject.addVelocity(bulletObject.getForwardVector(), bulletMag, tDelta);
		bulletObject.updateVel(tDelta);
	}
}

void shoot(double tDelta) {
	glm::vec2 bulletPos = player->getPosition() + (player->getForwardVector() * 5.0f);
	float bulletOrient = player->objectRef->orientation;

	bulletNum++;

	addObject("bullet"+bulletNum, bulletPos, bulletOrient, glm::vec2(2.0f, 2.0f), "Resources\\Textures\\bullet.png", TextureProperties::NearestFilterTexture());
	
}

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if a key is pressed
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// If escape is pressed tell GLFW we want to close the window (and quit)
			glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_W:
			wKey = true;
			break;
		case GLFW_KEY_A:
			aKey = true;
			break;
		case GLFW_KEY_S:
			sKey = true;
			break;
		case GLFW_KEY_D:
			dKey = true;
			break;
		case GLFW_KEY_SPACE:
			spaceKey = true;
			break;

		default:
		{
		}
		}
	}
	// If not check a key has been released
	else if (action == GLFW_RELEASE) {

		// check which key was released...
		switch (key)
		{
		case GLFW_KEY_W:
			wKey = false;
			break;
		case GLFW_KEY_A:
			aKey = false;
			break;
		case GLFW_KEY_S:
			sKey = false;
			break;
		case GLFW_KEY_D:
			dKey = false;
			break;
		case GLFW_KEY_SPACE:
			spaceKey = false;
			break;

		default:
		{
		}
		}
	}
}
