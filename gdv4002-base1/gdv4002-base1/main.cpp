#include "Engine.h"
#include "Player.h"
#include "Bullet.h"
#include "Astroid.h"
#include "animation.h"
#include <time.h>
#include <stdlib.h>
#include "enemyUFO.h"

// Function prototypes
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void playerControl(double);
void shoot(double);
void updateBullets(double);
void deleteBulletFromArray(Bullet* array, int index, int* arrSize);
void spawnMedAstroid(double, glm::vec2 pos);
//void deleteMedAstFromArray(int index);
void updateAstroids(double tDelta);
//void deleteFromArray(Bullet* array, int index, int* arrSize);
void deleteFromAstroidArray(Astroid* array, int index, int* arrSize);
void spawnSmallAstroid(double tDelta,glm::vec2 pos);
void spawnBigAstroid(double tDelta, glm::vec2 pos);
void spawnLevel(double tDelta);
void checkCompletion();
void checkPlayerHB(double tDelta);
void clearScene();
void updateAnim(double tDelta);
void updateUps(double tDelta);
void fullReset();
void enemyShoot(double tDelta, int index);
void enemyControl(double tDelta);
void ufoUpdateBullets(double tDelta);
void spawnUFO(double tDelta, glm::vec2 pos);
void deleteUFO(int index);

bool wKey, aKey, sKey, dKey,spaceKey = false;
int bulletNum = 0;

float bulletMag = 300.0f;
const float PI = 3.141593f;

const float levelDelay = 2.0f;
float cLevelDelay = 0.0f;

float forwardForce = 200.0f;

float width, height;

bool canShoot = false;

int bulletTexture, playerTexture, astroidBigTexture, astroidMediumTexture, astroidSmallTexture;

glm::vec2 BulletSize = glm::vec2(5,5);

Player* player;

Bullet* bullet = new Bullet[10];
int bulletIndex = 0;

Bullet* enemyBullet = new Bullet[10];
int enemyBulletIndex = 0;

float shotTimer = 1.0f;
float shotDelay = 0.1f;

Astroid* bigAstroidArr = new Astroid[30];
int bigAstroidIndex = 0;

Astroid* medAstroidArr = new Astroid[90];
int medAstroidIndex = 0;

Astroid* smallAstroidArr = new Astroid[330];
int smallAstroidIndex = 0;

int* gunFlareIDs = new int[4];
animation gunFlareAnimL, gunFlareAnimR;

int* healthTextIDs = new int[6];
GameObject2D healthBar;

GameObject healthUp, shieldUp;
const float pUpSpeed = 9.0f;

enemyUFO* UFO = new enemyUFO[10];
int UFOtexture;
int ufoBulletText;
float ufoShotDelay = 0.5f;
int ufoIndex = 0;
float ufoSpeed = 50.0f;


const int powerUpDespawn = 10.0f;
float healthUpTimer = 0.0f;
float shieldUpTimer = 0.0f;

int healthUpText;
int sheildUpText;

const int damageCoolDown = 1.0f;
float cDamageTimer = 0;

int currentLevel = 1;
const int maxLevel = 30;
bool levelInProgress = false;

const int baPerLevel = 1;
const int maPerLevel = 1;
const int saPerLevel = 2;
const float ufoPerLevel = 0.2f;


float bigAstroidSpeed = 10.0f;
float medAstroidSpeed = 20.0f;
float smallAstroidSpeed = 25.0f;

glm::vec4 bg = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

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

	width = getViewplaneWidth();
	height = getViewplaneHeight();

	srand(time(0));
	playerTexture = loadTexture("Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());
	bulletTexture = loadTexture("Resources\\Textures\\bullet.png", TextureProperties::NearestFilterTexture());
	astroidBigTexture = loadTexture("Resources\\Textures\\asteroid.png", TextureProperties::NearestFilterTexture());
	astroidSmallTexture = loadTexture("Resources\\Textures\\asteroid.png", TextureProperties::NearestFilterTexture());


	gunFlareIDs[0] = loadTexture("Resources\\Textures\\Gun Flare\\flare1.png", TextureProperties::NearestFilterTexture());
	gunFlareIDs[1] = loadTexture("Resources\\Textures\\Gun Flare\\flare2.png", TextureProperties::NearestFilterTexture());
	gunFlareIDs[2] = loadTexture("Resources\\Textures\\Gun Flare\\flare3.png", TextureProperties::NearestFilterTexture());
	gunFlareIDs[3] = loadTexture("Resources\\Textures\\Gun Flare\\flare4.png", TextureProperties::NearestFilterTexture());

	healthTextIDs[0] = loadTexture("Resources\\Textures\\Health\\bar0.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[1] = loadTexture("Resources\\Textures\\Health\\bar1.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[2] = loadTexture("Resources\\Textures\\Health\\bar2.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[3] = loadTexture("Resources\\Textures\\Health\\bar3.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[4] = loadTexture("Resources\\Textures\\Health\\bar4.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[5] = loadTexture("Resources\\Textures\\Health\\barSheild.png", TextureProperties::NearestFilterTexture());

	UFOtexture = loadTexture("Resources\\Textures\\enemyUFO.png", TextureProperties::NearestFilterTexture());
	ufoBulletText = loadTexture("Resources\\Textures\\enemyBullet.png", TextureProperties::NearestFilterTexture());

	healthUpText = loadTexture("Resources\\Textures\\healthUp.png", TextureProperties::NearestFilterTexture());
	sheildUpText = loadTexture("Resources\\Textures\\shieldUp.png", TextureProperties::NearestFilterTexture());

	GameObject2D tHU = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), healthUpText);
	GameObject2D tSU = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), sheildUpText);

	healthUp.makeNew(GameObject(&tHU));
	shieldUp.makeNew(GameObject(&tSU));

	healthUp.setVelocity(glm::vec2(glm::radians(-45.0f), glm::radians(-45.0f)), pUpSpeed);
	shieldUp.setVelocity(glm::vec2(glm::radians(-45.0f),glm::radians(-45.0f)), pUpSpeed);
	
	GameObject2D hb = GameObject2D(glm::vec2(-width / 2.0f + 10.0f, height / 2.0f - 2.5f), 0.0f, glm::vec2(20, 5), healthTextIDs[4]);

	addObject("healthBar", &hb);
	
	player = new Player(glm::vec2(0, 0), 0, playerTexture, glm::vec2(10,10), &hb, healthTextIDs);

	gunFlareAnimL.makeNew(animation(0.0f, gunFlareIDs, 4, glm::vec2(3, 3)));
	gunFlareAnimR.makeNew(animation(0.0f, gunFlareIDs, 4, glm::vec2(3, 3)));

	addObject("gunFlareAnim", &gunFlareAnimL);
	addObject("gunFlareAnim", &gunFlareAnimR);

	addObject("Player", player);

	addObject("shieldUp", &shieldUp);
	addObject("healthUp", &healthUp);
	
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

	updateAnim(tDelta);
	spawnLevel(tDelta);
	checkCompletion();

	playerControl(tDelta);
	player->keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, 5);

	enemyControl(tDelta);
	ufoUpdateBullets(tDelta);

	checkPlayerHB(tDelta);
	updateAstroids(tDelta);
	updateBullets(tDelta);
	updateUps(tDelta);
}

void updateAnim(double tDelta) {
	float fX = 5 * cos(player->orientation);
	float fY = 5 * sin(player->orientation);

	float lX = fX + (2 * cos(player->orientation + 90 * 180 / PI)) + player->position.x;
	float lY = fY + (2 * sin(player->orientation + 90 * 180 / PI)) + player->position.y;

	float rX = fX + (2 * cos(player->orientation - 90 * 180 / PI)) + player->position.x;
	float rY = fY + (2 * sin(player->orientation - 90 * 180 / PI)) + player->position.y;

	gunFlareAnimL.updateAnim(tDelta, glm::vec2(lX,lY));
	gunFlareAnimR.updateAnim(tDelta, glm::vec2(rX,rY));
}
void checkPlayerHB(double tDelta) {

	if (healthUp.checkColl(player)) {
		healthUp.position = glm::vec2(1000.0f, 1000.0f);
		player->addHealth();
	}
	if (shieldUp.checkColl(player)) {
		shieldUp.position = glm::vec2(1000.0f, 1000.0f);
		player->addSheild();
	}

	cDamageTimer += tDelta;
	if (cDamageTimer < damageCoolDown) {
		//do nothing
		return;
	}

	bool hit = false;
	
	glm::vec2 playerPos = player->getPosition();

	for (int ba = 0; ba < bigAstroidIndex; ba++) {
		if (bigAstroidArr[ba].checkColl(player)) {
			hit = true;
			bigAstroidArr[ba].addHit();
		}
	}

	for (int ma = 0; ma < medAstroidIndex; ma++) {
		if (medAstroidArr[ma].checkColl(player)) {
			hit = true;
			medAstroidArr[ma].addHit();
		}
	}

	for (int sa = 0; sa < smallAstroidIndex; sa++) {
		if (smallAstroidArr[sa].checkColl(player)) {
			hit = true;
			smallAstroidArr[sa].addHit();
		}
	}

	if (hit) {
		cDamageTimer = 0.0f;
		if (player->reduceHealth()) {

			currentLevel = 1;
			levelInProgress = false;
			fullReset();

		}
	}

}

void checkCompletion() {
	if (bigAstroidIndex + medAstroidIndex + smallAstroidIndex + ufoIndex == 0 && levelInProgress) {
		cLevelDelay = 0.0f;

		levelInProgress = false;
		if (currentLevel != maxLevel) {
			currentLevel++;
		}
	}
}

void spawnLevel(double tDelta) {
	cLevelDelay += tDelta;
	if (levelInProgress || cLevelDelay < levelDelay) {
		//do nothing
		return;
	} else {
		levelInProgress = true;

		clearScene(); 

		for (int ba = 0; ba < baPerLevel * currentLevel; ba++) {
			float xPos = 0;
			float yPos = 0;
			if (rand() % 2 < 1) {
				xPos = rand() % (int)width - width / 2.0f;
				yPos = height / 2.0f + 10.0f;
			}
			else {
				yPos = rand() % (int)height - height / 2.0f;
				xPos = width / 2.0f + 10.0f;
			}
			spawnBigAstroid(0.0f, glm::vec2(xPos, yPos));
		}

		for (int ma = 0; ma < maPerLevel * currentLevel; ma++) {
			float xPos = 0;
			float yPos = 0;
			if (rand() % 2 < 1) {
				xPos = rand() % (int)width - width / 2.0f;
				yPos = height / 2.0f + 10.0f;
			}
			else {
				yPos = rand() % (int)height - height / 2.0f;
				xPos = width / 2.0f + 10.0f;
			}
			spawnMedAstroid(0.0f, glm::vec2(xPos, yPos));
		}

		for (int sa = 0; sa < saPerLevel * currentLevel; sa++) {
			float xPos = 0;
			float yPos = 0;
			if (rand() % 2 < 1) {
				xPos = rand() % (int)width - width / 2.0f;
				yPos = height / 2.0f + 10.0f;
			}
			else {
				yPos = rand() % (int)height - height / 2.0f;
				xPos = width / 2.0f + 10.0f;
			}
			spawnSmallAstroid(0.0f, glm::vec2(xPos, yPos));
		}
		for (int ufo = 0; ufo < (int) (ufoPerLevel * currentLevel); ufo++) {
			float xPos = 0;
			float yPos = 0;

			yPos = rand() % (int)height/2.0f;
			xPos = width / 2.0f + 10.0f;

			spawnUFO(tDelta, glm::vec2(xPos, yPos));
		}
	}
}

void spawnPUp(GameObject* powerUp, glm::vec2 pos) {

	float ori = glm::radians(rand() % 360 * 1.0f);

	powerUp->orientation = ori;
	powerUp->setVelocity(powerUp->getForwardVector(), pUpSpeed);
	powerUp->position = pos;

	powerUp->orientation = 0;

}

void updateUps(double tDelta) {
	if (healthUp.position.x < 100) {
		healthUp.updateVel(tDelta);
		healthUp.keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, healthUp.size.x / 2.0f);

		healthUpTimer += tDelta;
		if (healthUpTimer > powerUpDespawn) {
			healthUp.position = glm::vec2(1000.0f, 1000.0f);
		}
	}
	else {
		//do nothing
	}

	if (shieldUp.position.x < 100) {
		shieldUp.updateVel(tDelta);
		shieldUp.keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, shieldUp.size.x / 2.0f);

		shieldUpTimer += tDelta;
		if (shieldUpTimer > powerUpDespawn) {
			shieldUp.position = glm::vec2(1000.0f, 1000.0f);
		}
	}
	else {
		//do nothing
	}
}

void updateAstroids(double tDelta) {
	for (int ba = 0; ba < bigAstroidIndex; ba++) {
		bigAstroidArr[ba].updateVel(tDelta);
		bigAstroidArr[ba].keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, bigAstroidArr[ba].size.x/2.0f);
	}
	

	for (int ma = 0; ma < medAstroidIndex; ma++) {
		medAstroidArr[ma].updateVel(tDelta);
		medAstroidArr[ma].keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, medAstroidArr[ma].size.x / 2.0f);
	}

	for (int sa = 0; sa < smallAstroidIndex; sa++) {
		smallAstroidArr[sa].updateVel(tDelta);
		smallAstroidArr[sa].keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, smallAstroidArr[sa].size.x / 2.0f);
	}
}

void enemyControl(double tDelta) {
	for (int i = 0; i < ufoIndex; i++) {
		UFO[i].ufoShotTimer += tDelta;

		if (UFO[i].ufoShotTimer > ufoShotDelay) {
			enemyShoot(tDelta, i);
			UFO[i].ufoShotTimer = 0;
		}
		UFO[i].updateVel(tDelta);
		UFO[i].keepOnScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f, UFO[i].size.x / 2.0f);
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
			deleteBulletFromArray(bullet, i, &bulletIndex);

		}
		glm::vec2 hitPos;
		bool hit = false;

		for (int ufo = 0; ufo < ufoIndex; ufo++) {
			if (UFO[ufo].checkColl(bullet[i])) {
				hitPos = UFO[ufo].getPosition();
				deleteBulletFromArray(bullet, i, &bulletIndex);
				if (UFO[ufo].reduceHealth()) {
					deleteUFO(ufo);
					hit = true;
				}
			}
		}

		for (int ba = 0; ba < bigAstroidIndex; ba++) {
			if (bigAstroidArr[ba].checkColl(bullet[i])) {
				hitPos = bigAstroidArr[ba].getPosition();
				deleteBulletFromArray(bullet, i, &bulletIndex);
				if (bigAstroidArr[ba].addHit()) {
					spawnMedAstroid(tDelta, bigAstroidArr[ba].position);
					spawnMedAstroid(tDelta, bigAstroidArr[ba].position);

					bigAstroidArr[ba].makeNew(new Astroid());
					bigAstroidArr[ba].position = glm::vec2(10000.0f, 10000.0f);

					deleteFromAstroidArray(bigAstroidArr, ba, &bigAstroidIndex);

					hit = true;
				}
			}
		}

		for (int ma = 0; ma < medAstroidIndex; ma++) {
			if (medAstroidArr[ma].checkColl(bullet[i])) {
				hitPos = medAstroidArr[ma].getPosition();
				deleteBulletFromArray(bullet, i, &bulletIndex);
				if (medAstroidArr[ma].addHit()) {
					spawnSmallAstroid(tDelta, medAstroidArr[ma].position);
					spawnSmallAstroid(tDelta, medAstroidArr[ma].position);
					spawnSmallAstroid(tDelta, medAstroidArr[ma].position);

					medAstroidArr[ma].makeNew(new Astroid());
					medAstroidArr[ma].position = glm::vec2(10000.0f, 10000.0f);

					deleteFromAstroidArray(medAstroidArr, ma, &medAstroidIndex);

					hit = true;
				}
			}
		}

		for (int sa = 0; sa < smallAstroidIndex; sa++) {
			if (smallAstroidArr[sa].checkColl(bullet[i])) {
				hitPos = smallAstroidArr[sa].getPosition();
				deleteBulletFromArray(bullet, i, &bulletIndex);
				if (smallAstroidArr[sa].addHit()) {
					smallAstroidArr[sa].makeNew(new Astroid());

					smallAstroidArr[sa].position = glm::vec2(10000.0f, 10000.0f);

					deleteFromAstroidArray(smallAstroidArr, sa, &smallAstroidIndex);

					hit = true;
				}
			}
		}

		if (hit) {
			

			if (healthUp.position.x < 100) {
				//do nothing
			}
			else {
				int chance = rand() % 100 + 1;
				if (chance < 3) {
					spawnPUp(&healthUp, hitPos);
					healthUpTimer = 0;
				}
			}

			if (shieldUp.position.x < 100) {
				//do nothing
			}
			else {
				int chance = rand() % 100 + 1;
				if (chance < 2) {
					spawnPUp(&shieldUp, hitPos);
					shieldUpTimer = 0;
				}
			}
		}
	}
}

void ufoUpdateBullets(double tDelta) {
	for (int i = 0; i < enemyBulletIndex; i++) {
		if (!enemyBullet[i].deleteOffScreen(getViewplaneWidth() / 2.0f, getViewplaneHeight() / 2.0f)) {
			//do nothing
		}
		else {
			deleteBulletFromArray(enemyBullet, i, &enemyBulletIndex);
			

		}

		if (enemyBullet[i].checkColl(player)) {
			if (player->reduceHealth()) {
				fullReset();
			}
			deleteBulletFromArray(enemyBullet, i, &enemyBulletIndex);
		}

		enemyBullet[i].updateVel(tDelta);
	}
}

void spawnBigAstroid(double tDelta, glm::vec2 pos) {

	float ori = glm::radians(rand() % 360 * 1.0f);
	float rotSpeed = rand() % 50 + 70 * 1.0f;

	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	int size = rand() % 5 + 28;

	bigAstroidArr[bigAstroidIndex].makeNew(Astroid(pos, ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 0));
	addObject("bigAstroid", &bigAstroidArr[bigAstroidIndex]);

	bigAstroidArr[bigAstroidIndex].setVelocity(bigAstroidArr[bigAstroidIndex].getForwardVector(), bigAstroidSpeed);

	bigAstroidIndex++;
}

void spawnMedAstroid(double tDelta, glm::vec2 pos) {

	float ori = glm::radians(rand() % 360 * 1.0f);
	float rotSpeed = rand() % 50 + 100 * 1.0f;

	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	int size = rand()%5+18;

	medAstroidArr[medAstroidIndex].makeNew(Astroid(pos, ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 1));
	addObject("medAstroid", &medAstroidArr[medAstroidIndex]);

	medAstroidArr[medAstroidIndex].setVelocity(medAstroidArr[medAstroidIndex].getForwardVector(), medAstroidSpeed);

	medAstroidIndex++;
}

void spawnSmallAstroid(double tDeltam, glm::vec2 pos) {

	float ori = glm::radians(rand() % 360 * 1.0f);
	float rotSpeed = rand() % 50 + 140 * 1.0f;

	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	int size = rand() % 5 + 8;

	smallAstroidArr[smallAstroidIndex].makeNew(Astroid(pos, ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 2));
	addObject("smallAstroid", &smallAstroidArr[smallAstroidIndex]);

	smallAstroidArr[smallAstroidIndex].setVelocity(smallAstroidArr[smallAstroidIndex].getForwardVector(), smallAstroidSpeed);

	smallAstroidIndex++;
}

void spawnUFO(double tDelta, glm::vec2 pos) {

	float speed = rand() % 6 + ufoSpeed - 3;
	if (rand() % 2 < 1) {
		speed = -speed;
	}

	UFO[ufoIndex].makeNew(enemyUFO(pos, 0, UFOtexture, glm::vec2(10.0f, 10.0f)));
	addObject("enemyUFO", &UFO[ufoIndex]);

	UFO[ufoIndex].setVelocity(UFO[ufoIndex].getForwardVector(), speed);

	ufoIndex++;
}

void clearScene() {
	deleteMatchingObjects("bullet");
	bulletIndex = 0;

	deleteMatchingObjects("bigAstroid");
	bigAstroidIndex = 0;

	deleteMatchingObjects("medAstroid");
	medAstroidIndex = 0;

	deleteMatchingObjects("smallAstroid");
	smallAstroidIndex = 0;

	deleteMatchingObjects("enemyUFO");
	ufoIndex = 0;
}

void fullReset() {
	clearScene();
	player->position = glm::vec2(0,0);
	healthUp.position = glm::vec2(1000.0f, 1000.0f);
	shieldUp.position = glm::vec2(1000.0f, 1000.0f);
	player->setFullHealth();
	player->velocity = glm::vec2(0,0);
}

void deleteUFO(int index) {

	enemyUFO temp = UFO[index];

	for (int i = index; i < ufoIndex - 1; i++) {
		UFO[i].makeNew(UFO[i + 1]);
	}
	ufoIndex--;
	UFO[ufoIndex].makeNew(enemyUFO());
	UFO[ufoIndex].position = glm::vec2(10000.0f, 10000.0f);

	deleteObject(&temp);
}

void deleteBulletFromArray(Bullet* array, int index, int* arrSize) {
	
	Bullet temp = array[index];

	for (int i = index; i < (*arrSize) - 1; i++) {
		array[i].makeNew(array[i + 1]);
	}
	(*arrSize)--;
	array[*arrSize].makeNew(Bullet());
	array[*arrSize].position = glm::vec2(10000.0f, 10000.0f);

	deleteObject(&temp);
}

void deleteFromAstroidArray(Astroid* array, int index, int* arrSize) {
	
	Astroid temp = array[index];

	for (int i = index; i < (*arrSize) - 1; i++) {
		array[i].makeNew(array[i + 1]);
	}
	(*arrSize)--;
	array[*arrSize].makeNew(Astroid());
	array[*arrSize].position = glm::vec2(10000.0f, 10000.0f);

	deleteObject(&temp);
}

void enemyShoot(double tDelta, int index) {
	enemyBullet[enemyBulletIndex].makeNew(UFO[index].shoot(tDelta, bulletMag, ufoBulletText, BulletSize));
	enemyBullet[enemyBulletIndex].setVelocity(enemyBullet[enemyBulletIndex].getForwardVector(), bulletMag);

	addObject("bullet", &enemyBullet[enemyBulletIndex]);
	enemyBulletIndex++;
}

void shoot(double tDelta) {
	bullet[bulletIndex].makeNew(player->shoot(tDelta, bulletMag, bulletTexture, BulletSize,&gunFlareAnimL,&gunFlareAnimR));
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

			delete[] bigAstroidArr;
			delete[] medAstroidArr;
			delete[] smallAstroidArr;
			delete[] bullet;

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
