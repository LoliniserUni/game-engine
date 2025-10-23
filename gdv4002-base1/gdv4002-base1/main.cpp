#include "Engine.h"

// Function prototypes
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void playerControl(double);

bool wKey, aKey, sKey, dKey = false;


const float PI = 3.141593f;

bool isSpinning = false;
float cRotVel;
float rotAccel = 30.0f;
float maxRot = 10.0f;

float cSpeed;
float maxSpeed = 50.0f;
float forwardAccel = 15.0f;
float backwardsAccel = 25.0f;
float driftLoss = 1.0f * 180/PI;

float newX, newY;

float cVelOrientation;

const float rotSpeed = glm::radians(360.0f);

GameObject2D* player;

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024,100.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("player",glm::vec2(10.0f,10.0f),glm::radians(270.0f),glm::vec2(10.0f,10.0f),"Resources\\Textures\\player1_ship.png",TextureProperties::NearestFilterTexture());

	player = getObject("player");

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

	

}

void playerControl(double tDelta) {
	if (aKey) {
		/*if (cRotVel <= maxRot) {

			cRotVel += tDelta * rotAccel;
		}*/

		cRotVel = maxRot;

		player->orientation = player->orientation + (cRotVel * tDelta);
	}
	if (dKey) {
		/*if (cRotVel >= -1.0 * maxRot) {

			cRotVel -= tDelta * rotAccel;
		}*/

		cRotVel = maxRot * -1.0;

		player->orientation = player->orientation + (cRotVel * tDelta);
	}
	if (wKey) {
		if (cSpeed < maxSpeed) {
			cSpeed += forwardAccel * tDelta;
		}

		cVelOrientation = player->orientation;
		
	}
	if (sKey) {
		if (cSpeed > 0.00001) {
			cSpeed -= backwardsAccel * tDelta;
		}
	}

	newX = (cSpeed * tDelta * cos(cVelOrientation)) + player->position.x;
	newY = (cSpeed * tDelta * sin(cVelOrientation)) + player->position.y;

	player->position = glm::vec2(newX, newY);

	//player->orientation = player->orientation + (cRotVel * tDelta);
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

		default:
		{
		}
		}
	}
}
