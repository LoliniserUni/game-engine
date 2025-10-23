#include "Engine.h"
#include "myGameObject.h"

// Function prototypes
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void playerControl(double);
void keepPlayerOnScreen();

bool wKey, aKey, sKey, dKey = false;


const float PI = 3.141593f;

float forwardForce = 0.2f;

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
	keepPlayerOnScreen();
}
void keepPlayerOnScreen() {
	glm::vec2 pos = player->getPosition();
	float viewWidth = getViewplaneWidth()/2;
	float viewHeight = getViewplaneHeight()/2;

	if (pos.x > viewWidth) {
		player->objectRef->position.x = -1.0 * viewWidth;
	}
	if (pos.x < -1.0 * viewWidth) {
		player->objectRef->position.x = viewWidth;
	}
	if (pos.y > viewHeight) {
		player->objectRef->position.y = -1.0 * viewHeight;
	}
	if (pos.y < -1.0 * viewHeight) {
		player->objectRef->position.y = viewHeight;
	}
}
void playerControl(double tDelta) {
	if (aKey) {
		player->turnLeft(tDelta);
	}
	if (dKey) {
		player->turnRight(tDelta);
	}
	if (wKey) {
		player->addVelocity(player->getForwardVector(), forwardForce);
	}
	if (sKey) {
		player->addVelocity(player->getForwardVector(), forwardForce*-1.0);
	}

	player->updateVel(tDelta);
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
