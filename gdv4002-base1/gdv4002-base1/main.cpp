#include "Engine.h"
#include "Player.h"
#include "Bullet.h"

// Function prototypes
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void playerControl(double);
void shoot(double);
void updateBullets(double);
void deleteBulletFromArray(int);

bool wKey, aKey, sKey, dKey,spaceKey = false;
int bulletNum = 0;

float bulletMag = 300.0f;
const float PI = 3.141593f;

float forwardForce = 200.0f;

float width, height;

bool canShoot = false;

int bulletTexture, playerTexture;

glm::vec2 BulletSize = glm::vec2(5,5);

Player* player;
Bullet* bullet = new Bullet[10];
int bulletIndex = 0;

float shotTimer = 1.0f;
float shotDelay = 0.1f;

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

	
	playerTexture = loadTexture("Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());
	bulletTexture = loadTexture("Resources\\Textures\\bullet.png", TextureProperties::NearestFilterTexture());

	player = new Player(glm::vec2(85, 85), 1.0f/4.0f*-PI, playerTexture, glm::vec2(10,10));
	addObject("Player",player);
	//glm::vec4 bg = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);


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
	shotTimer += (float)tDelta;
	if (shotTimer >= shotDelay) {
		canShoot = true;
	}
	else {
		canShoot = false;
	}

	playerControl(tDelta);
	player->keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f);

	updateBullets(tDelta);
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
	}if (spaceKey && canShoot) {
		shoot(tDelta);
		shotTimer = 0.0f;
	}
	player->updateVel(tDelta);
}

void updateBullets(double tDelta) {
	for (int i = 0; i < bulletIndex; i++) {
		bullet[i].updateVel(tDelta);
		
		/*bullet[i].keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f);
		if (!bullet[i].reduceTime(tDelta)) {
			//do nothing
		}
		else {
			deleteBulletFromArray(i);
		}*/
		if (!bullet[i].deleteOffScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f)) {
			//do nothing
		}
		else {
			deleteBulletFromArray(i);
		}
	}
}

void deleteBulletFromArray(int index) {
	for (int i = index; i < bulletIndex-1; i++) {
		bullet[i].makeNew(bullet[i + 1]);
	}
	bulletIndex--;
	bullet[bulletIndex].makeNew(Bullet());
	bullet[index - 1].position = glm::vec2(10000.0f, 10000.0f);
	deleteObject(&bullet[index-1]);
	
}
void shoot(double tDelta) {
	printf("Shoot,%d\n", bulletIndex);
	bullet[bulletIndex].makeNew(player->shoot(tDelta, bulletMag, bulletTexture, BulletSize));
	bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

	addObject("bullet", &bullet[bulletIndex]);
	bulletIndex++;
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
