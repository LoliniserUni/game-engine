#include "Engine.h"
#include "Player.h"
#include "Bullet.h"
#include "Astroid.h"
#include <time.h>
#include <stdlib.h>

// Function prototypes
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void playerControl(double);
void shoot(double);
void updateBullets(double);
void deleteBulletFromArray(int);
void spawnMedAstroid(double);
void deleteMedAstFromArray(int index);
void updateAstroids(double tDelta);
void deleteFromArray(GameObject* array, int index, int* arrSize);
void spawnSmallAstroid(double tDelta);

bool wKey, aKey, sKey, dKey,spaceKey = false;
int bulletNum = 0;

float bulletMag = 300.0f;
const float PI = 3.141593f;

float forwardForce = 200.0f;

float width, height;

bool canShoot = false;

int bulletTexture, playerTexture, astroidBigTexture, astroidMediumTexture, astroidSmallTexture;

glm::vec2 BulletSize = glm::vec2(5,5);

Player* player;
Bullet* bullet = new Bullet[100];
int bulletIndex = 0;

float shotTimer = 1.0f;
float shotDelay = 0.1f;

Astroid astroid = new Astroid();

Astroid* bigAstroidArr = new Astroid[10];
int bigAstroidIndex = 0;

Astroid* medAstroidArr = new Astroid[10];
int medAstroidIndex = 0;

Astroid* smallAstroidArr = new Astroid[10];
int smallAstroidIndex = 0;

bool astroidExists = true;


float bigAstroidSpeed = 30.0f;
float medAstroidSpeed = 60.0f;
float smallAstroidSpeed = 90.0f;

glm::vec4 bg = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

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

	srand(time(0));
	playerTexture = loadTexture("Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());
	bulletTexture = loadTexture("Resources\\Textures\\bullet.png", TextureProperties::NearestFilterTexture());
	astroidBigTexture = loadTexture("Resources\\Textures\\asteroid.png", TextureProperties::NearestFilterTexture());
	astroidSmallTexture = loadTexture("Resources\\Textures\\asteroid.png", TextureProperties::NearestFilterTexture());

	astroid.makeNew(Astroid(glm::vec2(2.0f,5.0f), 0.0f, astroidBigTexture, glm::vec2(30,30), glm::radians(100.0f), 0));
	astroid.setVelocity(astroid.getForwardVector(), bigAstroidSpeed);

	
	player = new Player(glm::vec2(0, 0), 0, playerTexture, glm::vec2(10,10));
	addObject("Player", player);

	//addObject("Astroid", &astroid);


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
	updateAstroids(tDelta);

	

	playerControl(tDelta);
	player->keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, 5);

	updateBullets(tDelta);
}

void updateAstroids(double tDelta) {
	if (astroidExists) {
		astroid.updateVel(tDelta);
		astroid.keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, 15);
	}
	

	for (int ma = 0; ma < medAstroidIndex; ma++) {
		medAstroidArr[ma].updateVel(tDelta);
		medAstroidArr[ma].keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, 15);
	}
}
void playerControl(double tDelta) {

	shotTimer += (float)tDelta;
	if (shotTimer > shotDelay) {
		canShoot = true;
	}
	else {
		canShoot = false;
	}

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

		if (!bullet[i].deleteOffScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f)) {
			//do nothing
		}
		else {
			printf("Pre Size: %d\n", bulletIndex);
			deleteFromArray(bullet, i, &bulletIndex);
			//deleteBulletFromArray(i);

		}
		/*if (astroidExists) {
			float bx = bullet[i].getPosition().x;
			float by = bullet[i].getPosition().y;

			float ax = astroid.getPosition().x;
			float ay = astroid.getPosition().y;

			float xDif = abs(bx - ax);
			float yDif = abs(bx - ax);

			if (xDif < astroid.size.x / 2.0f && yDif < astroid.size.y / 2.0f) {
				astroid.makeNew(new Astroid());
				spawnMedAstroid(tDelta);
				spawnMedAstroid(tDelta);

				deleteBulletFromArray(i);
				astroidExists = false;
			}
		}

		for (int ma = 0; ma < medAstroidIndex; ma++) {
			printf("%d", ma);
			float bx = bullet[i].getPosition().x;
			float by = bullet[i].getPosition().y;


			float ax = medAstroidArr[ma].getPosition().x;
			float ay = medAstroidArr[ma].getPosition().y;

			float xDif = abs(bx - ax);
			float yDif = abs(bx - ax);

			if (xDif < medAstroidArr[ma].size.x / 2.0f && yDif < medAstroidArr[ma].size.y / 2.0f) {
				medAstroidArr[ma].makeNew(new Astroid());

				printf("%Delete %d", ma);

				deleteBulletFromArray(i);
				deleteMedAstFromArray(ma);

				spawnSmallAstroid(tDelta);
				spawnSmallAstroid(tDelta);
			}
		}*/
	}
}

void spawnMedAstroid(double tDelta) {
	float width = getViewplaneWidth();
	float height = getViewplaneHeight();

	float x = 0;
	float y = 0;

	if (rand() % 2 < 1) {
		x = (rand() % (int) width) - width / 2;
		y = height / 2;
	}
	else {
		y = (rand() % (int)height) - height / 2;
		x = width / 2;
	}

	float ori = glm::radians(rand() % 360 * 1.0f);
	float rotSpeed = rand() % 50 + 100 * 1.0f;

	int size = rand()%3+14;

	medAstroidArr[medAstroidIndex].makeNew(Astroid(glm::vec2(x, y), ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 1));
	addObject("medAstroid", &medAstroidArr[medAstroidIndex]);

	medAstroidArr[medAstroidIndex].setVelocity(medAstroidArr[medAstroidIndex].getForwardVector(), medAstroidSpeed);

	medAstroidIndex++;
}

void spawnSmallAstroid(double tDelta) {
	float width = getViewplaneWidth();
	float height = getViewplaneHeight();

	float x = 0;
	float y = 0;

	if (rand() % 2 < 1) {
		x = (rand() % (int)width) - width / 2;
		y = height / 2;
	}
	else {
		y = (rand() % (int)height) - height / 2;
		x = width / 2;
	}

	float ori = glm::radians(rand() % 360 * 1.0f);
	float rotSpeed = rand() % 50 + 140 * 1.0f;

	int size = rand() % 3 + 9;

	smallAstroidArr[smallAstroidIndex].makeNew(Astroid(glm::vec2(x, y), ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 1));
	addObject("medAstroid", &medAstroidArr[smallAstroidIndex]);

	smallAstroidArr[smallAstroidIndex].setVelocity(smallAstroidArr[smallAstroidIndex].getForwardVector(), smallAstroidSpeed);

	smallAstroidIndex++;
}

void deleteFromArray(GameObject* array, int index, int* arrSize) {

    for (int i = index; i < (*arrSize) - 1; i++) {
		array[i].makeNew(array[i + 1]);
	}
	(*arrSize)--;
	array[*arrSize].makeNew(GameObject());
	array[*arrSize].position = glm::vec2(10000.0f, 10000.0f);
}

void deleteBulletFromArray(int index) {
	for (int i = index; i < bulletIndex-1; i++) {
		bullet[i].makeNew(bullet[i + 1]);
	}
	bulletIndex--;
	bullet[bulletIndex].makeNew(Bullet());
	bullet[bulletIndex].position = glm::vec2(10000.0f, 10000.0f);
}

void deleteMedAstFromArray(int index) {
	for (int i = index; i < medAstroidIndex; i++) {
		medAstroidArr[i].makeNew(medAstroidArr[i + 1]);
	}
	printf("%d", medAstroidIndex);
	medAstroidArr[medAstroidIndex].makeNew(Astroid());
	medAstroidArr[medAstroidIndex].position = glm::vec2(10000.0f, 10000.0f);

}

void deleteSmallAstFromArray(int index) {
	for (int i = index; i < smallAstroidIndex; i++) {
		medAstroidArr[i].makeNew(medAstroidArr[i + 1]);
	}
	printf("%d", smallAstroidIndex);
	medAstroidArr[smallAstroidIndex].makeNew(Astroid());
	medAstroidArr[smallAstroidIndex].position = glm::vec2(10000.0f, 10000.0f);

}
void shoot(double tDelta) {
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
