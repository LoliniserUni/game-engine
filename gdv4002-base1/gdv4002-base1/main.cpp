#include "Engine.h"
#include "Player.h"
#include "Bullet.h"
#include "Astroid.h"
#include "Animation.h"
#include <time.h>
#include <stdlib.h>
#include "EnemyUFO.h"

// Function prototypes
void shoot2(double tDelta);
void myUpdateScene(GLFWwindow*,double);
void myKeyboardHandler(GLFWwindow*, int, int, int, int);
void myRenderFunction(GLFWwindow* window);

void playerControl(double);
void enemyControl(double tDelta);

void shoot(double);
void enemyShoot(double tDelta, int index);

void updateBullets(double);
void ufoUpdateBullets(double tDelta);
void updateAstroids(double tDelta);
void updateAnim(double tDelta);
void updateUps(double tDelta);

void checkPlayerHB(double tDelta);

void deleteBulletFromArray(Bullet* array, int index, int* arrSize);
void deleteFromAstroidArray(Astroid* array, int index, int* arrSize);
void deleteUFO(int index);

void spawnMedAstroid(double, glm::vec2 pos);
void spawnSmallAstroid(double tDelta, glm::vec2 pos);
void spawnBigAstroid(double tDelta, glm::vec2 pos);
void spawnUFO(double tDelta, glm::vec2 pos);
void spawnPUp(GameObject* powerUp, glm::vec2 pos);

void spawnLevel(double tDelta);
void checkCompletion();

void clearScene();
void fullReset();
void releaseMemory();

void spawnBackgrounfParticles(double tDelta, glm::vec2 pos, int index);

// Player controls and variables
Player* player = nullptr;
Player* player2 = nullptr;

bool wKey = false, aKey = false, sKey = false, dKey = false, spaceKey = false, leftShift = false;
bool key8 = false, key4 = false, key5 = false, key6 = false, rightKey = false, downKey = false;
const float forwardForce = 10000.0f;

const float damageCoolDown = 1.0f;
float cDamageTimer = 0;
float cDamageTimer2 = 0;

bool hasTrippleShot = false;
bool hasTrippleShot2 = false;

// Bullet related variables
int bulletNum = 0;
const float bulletMag = 300.0f;
bool canShoot = false;
bool canShoot2 = false;

float shotTimer = 1.0f;

float shotTimer2 = 1.0f;
float shotDelay = 0.1f;

float shotDelay2 = 0.1f;

float stdDelay = 0.1f;
float boostedDelay = 0.05f;

float boostedDelayTimer = 0.0f;

float boostedDelayTimer2 = 0.0f;
float boostedShotLen = 8.0f;

float trippleShotLen = 0.0f;
float trippleShotLen2 = 0.0f;
// Level related variables
const float levelDelay = 2.0f;
float cLevelDelay = 0.0f;
float width = 0, height = 0;

int currentLevel = 1;
const int maxLevel = 30;
bool levelInProgress = false;

// Amounts of objects per level (eg: level 5 will have 5 big asteroids, 5 medium asteroids, 10 small asteroids and 1 UFO
const int baPerLevel = 1;
const int maPerLevel = 1;
const int saPerLevel = 2;
const float ufoPerLevel = 0.2f;

// Object arrays, variable size is set the the maximum of that object that could possibly be in my scene at a given time
int maxBul = 96;
Bullet* bullet = new Bullet[maxBul];
int bulletIndex = 0;

int maxEnemyBul = 20;
Bullet* enemyBullet = new Bullet[maxEnemyBul];
int enemyBulletIndex = 0;

int maxBAs = maxLevel * baPerLevel;
Astroid* bigAstroidArr = new Astroid[maxBAs];
int bigAstroidIndex = 0;

int maxMAs = maxBAs + maPerLevel * maxLevel;
Astroid* medAstroidArr = new Astroid[maxMAs];
int medAstroidIndex = 0;

int maxSAs = maxMAs + saPerLevel * maxLevel;
Astroid* smallAstroidArr = new Astroid[maxSAs];
int smallAstroidIndex = 0;

int maxUFO = (int)(ufoPerLevel * maxLevel);
EnemyUFO* UFO = new EnemyUFO[maxUFO];
int ufoIndex = 0;

GameObject2D earth, background;

GameObject* backgroundParticles = new GameObject[100];

// Enemy UFO varables and asteroid
const float ufoShotDelay = 0.5f;
const float ufoSpeed = 50.0f;

const float bigAstroidSpeed = 10.0f;
const float medAstroidSpeed = 20.0f;
const float smallAstroidSpeed = 25.0f;

// background colours
const glm::vec4 hitBG = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 normalBG = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

// textures
int bulletTexture, playerTexture2, playerTexture, astroidBigTexture, astroidMediumTexture, astroidSmallTexture, UFOtexture, ufoBulletText, healthUpText, sheildUpText, fireRateUpText, trippleShotText, cloverText, startText;
const glm::vec2 BulletSize = glm::vec2(5, 5);

// Animation objects for both the players muzzle flash and my ufos muzzle flash
int* blueGunFlareIDs = new int[4];
int* gunFlareIDs = new int[4];
Animation gunFlareAnimL, gunFlareAnimR;

Animation gunFlareAnimL2, gunFlareAnimR2;
Animation* UFOgunFlare = new Animation[maxUFO];


// Other sprite objects
int* healthTextIDs = new int[5];

GameObject healthUp, shieldUp, fireRateUp, trippleShot, clover;
const float pUpSpeed = 9.0f;

// Power up variables
const float powerUpDespawn = 10.0f;
float healthUpTimer = 0.0f;
float shieldUpTimer = 0.0f;
float fireRateTimer = 0.0f;
float trippleShotTimer = 0.0f;
float cloverDespawnTimer = 0.0f;

// score counter
int score;

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
	
	// seting the viewplane width and height variables
	width = getViewplaneWidth();
	height = getViewplaneHeight();

	srand((unsigned int) time(0));

	hideAxisLines();
	//setting all the various textures 

	std::cout << "loading textures" << std::endl;

	playerTexture = loadTexture("Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());
	playerTexture2 = loadTexture("Resources\\Textures\\player2_ship.png", TextureProperties::NearestFilterTexture());
	bulletTexture = loadTexture("Resources\\Textures\\bullet.png", TextureProperties::NearestFilterTexture());
	astroidBigTexture = loadTexture("Resources\\Textures\\asteroid.png", TextureProperties::NearestFilterTexture());
	astroidSmallTexture = loadTexture("Resources\\Textures\\asteroid.png", TextureProperties::NearestFilterTexture());


	gunFlareIDs[0] = loadTexture("Resources\\Textures\\Gun Flare\\flare1.png", TextureProperties::NearestFilterTexture());
	gunFlareIDs[1] = loadTexture("Resources\\Textures\\Gun Flare\\flare2.png", TextureProperties::NearestFilterTexture());
	gunFlareIDs[2] = loadTexture("Resources\\Textures\\Gun Flare\\flare3.png", TextureProperties::NearestFilterTexture());
	gunFlareIDs[3] = loadTexture("Resources\\Textures\\Gun Flare\\flare4.png", TextureProperties::NearestFilterTexture());

	blueGunFlareIDs[0] = loadTexture("Resources\\Textures\\Enemy Gun Flare\\1.png", TextureProperties::NearestFilterTexture());
	blueGunFlareIDs[1] = loadTexture("Resources\\Textures\\Enemy Gun Flare\\2.png", TextureProperties::NearestFilterTexture());
	blueGunFlareIDs[2] = loadTexture("Resources\\Textures\\Enemy Gun Flare\\3.png", TextureProperties::NearestFilterTexture());
	blueGunFlareIDs[3] = loadTexture("Resources\\Textures\\Enemy Gun Flare\\4.png", TextureProperties::NearestFilterTexture());

	healthTextIDs[0] = loadTexture("Resources\\Textures\\Health\\bar0.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[1] = loadTexture("Resources\\Textures\\Health\\bar1.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[2] = loadTexture("Resources\\Textures\\Health\\bar2.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[3] = loadTexture("Resources\\Textures\\Health\\bar3.png", TextureProperties::NearestFilterTexture());
	healthTextIDs[4] = loadTexture("Resources\\Textures\\Health\\bar4.png", TextureProperties::NearestFilterTexture());

	UFOtexture = loadTexture("Resources\\Textures\\EnemyUFO.png", TextureProperties::NearestFilterTexture());
	ufoBulletText = loadTexture("Resources\\Textures\\enemyBullet.png", TextureProperties::NearestFilterTexture());

	healthUpText = loadTexture("Resources\\Textures\\healthUp.png", TextureProperties::NearestFilterTexture());
	sheildUpText = loadTexture("Resources\\Textures\\shieldUp.png", TextureProperties::NearestFilterTexture());
	fireRateUpText = loadTexture("Resources\\Textures\\fireRateUp.webp", TextureProperties::NearestFilterTexture());
	trippleShotText = loadTexture("Resources\\Textures\\trippleShot.png", TextureProperties::NearestFilterTexture());
	cloverText = loadTexture("Resources\\Textures\\clover.png", TextureProperties::NearestFilterTexture());

	int earthText = loadTexture("Resources\\Textures\\earth.png", TextureProperties::NearestFilterTexture());
	earth = GameObject2D(glm::vec2(0, -width/2.0f), 0, glm::vec2(120.0f, 120.0f), earthText);

	int bgText = loadTexture("Resources\\Textures\\background.png", TextureProperties::NearestFilterTexture());
	background = GameObject2D(glm::vec2(0, 0), 0, glm::vec2(160.0f, 160.0f), bgText);

	int shieldIDText = loadTexture("Resources\\Textures\\shield.png", TextureProperties::NearestFilterTexture());


	std::cout << "textures loaded" << std::endl;

	GameObject2D* shield = new GameObject2D(glm::vec2(1000.0f, 1000.0f), 0,glm::vec2(15.0f,15.0f), shieldIDText);


	//creating objects, with correct textures and sizes. many i spawn off screen.
	GameObject2D tHU = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), healthUpText);
	GameObject2D tSU = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), sheildUpText);
	GameObject2D tFR = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), fireRateUpText);
	GameObject2D tTS = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), trippleShotText);
	GameObject2D tC = GameObject2D(glm::vec2(1000.0f, 1000.0f), 0, glm::vec2(8.0f, 8.0f), cloverText);

	healthUp.makeNew(GameObject(&tHU));
	healthUp.setMass(0.000000001f);
	shieldUp.makeNew(GameObject(&tSU));
	shieldUp.setMass(0.000000001f);
	fireRateUp.makeNew(GameObject(&tFR));
	fireRateUp.setMass(0.000000001f);
	trippleShot.makeNew(GameObject(&tTS));
	trippleShot.setMass(0.000000001f);
	clover.makeNew(GameObject(&tC));
	clover.setMass(0.000000001f);
	
	GameObject2D hb = GameObject2D(glm::vec2(-width / 2.0f + 10.0f, height / 2.0f - 2.5f), 0.0f, glm::vec2(20, 5), healthTextIDs[4]);
	GameObject2D hb2 = GameObject2D(glm::vec2(width / 2.0f - 10.0f, height / 2.0f - 2.5f), 0.0f, glm::vec2(20, 5), healthTextIDs[4]);

	player = new Player(glm::vec2(0, 0), 0, playerTexture, glm::vec2(10,10), &hb, healthTextIDs, shield);
	player2 = new Player(glm::vec2(0, 0), 0, playerTexture2, glm::vec2(10, 10), &hb2, healthTextIDs, shield);

	gunFlareAnimL.makeNew(Animation(0.0f, gunFlareIDs, 4, glm::vec2(3, 3)));
	gunFlareAnimR.makeNew(Animation(0.0f, gunFlareIDs, 4, glm::vec2(3, 3)));

	gunFlareAnimL2.makeNew(Animation(0.0f, gunFlareIDs, 4, glm::vec2(3, 3)));
	gunFlareAnimR2.makeNew(Animation(0.0f, gunFlareIDs, 4, glm::vec2(3, 3)));

	// Set custom render scene (for ui)
	setRenderFunction(myRenderFunction);

	//set keyboard handler and update fuction
	setKeyboardHandler(myKeyboardHandler);
	
	setUpdateFunction(myUpdateScene);

	startText = loadTexture("Resources\\Textures\\star.png", TextureProperties::NearestFilterTexture());
	for (int i = 0; i < 100; i++) {

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

		spawnBackgrounfParticles(0, glm::vec2(xPos, yPos), i);
	}

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	delete shield;

	// return success :)
	return 0;
}

// Update function
void myUpdateScene(GLFWwindow* window, double tDelta) {

	// Spawn level, and check the level win condition
	spawnLevel(tDelta);
	checkCompletion();

	// Control the player movement
	playerControl(tDelta);
	player->keepOnScreen(width / 2.0f, height / 2.0f);
	player2->keepOnScreen(width / 2.0f, height / 2.0f);
	
	// Control the enemy UFOs movement
	enemyControl(tDelta);
	ufoUpdateBullets(tDelta);

	// Check player hitbox
	checkPlayerHB(tDelta);

	// Update other objects and check their collisions
	updateAstroids(tDelta);
	updateBullets(tDelta);
	updateUps(tDelta);

	// Update Animations
	updateAnim(tDelta);

	earth.setOri(earth.getOri() + 0.005f * tDelta);

	for (int i = 0; i < 100; i++) {
		backgroundParticles[i].updateVel(tDelta);
		backgroundParticles[i].keepOnScreen(width / 2.0f, height / 2.0f);
	}

	if (player->alive || player2->alive) {
		//do nothing
	}
	else {
		fullReset();
	}
}

//update functions :D
void updateAstroids(double tDelta) {
	// For each asteroid, update its positions and keep it on the screen

	for (int ba = 0; ba < bigAstroidIndex; ba++) {
		bigAstroidArr[ba].updateVel(tDelta);
		bigAstroidArr[ba].keepOnScreen(width / 2.0f, height / 2.0f);

		for (int ba2 = 0; ba2 < bigAstroidIndex; ba2++) {
			if (ba2 != ba) {
				if (bigAstroidArr[ba].checkColl(&bigAstroidArr[ba2], tDelta)) {
					bigAstroidArr[ba].addHit();
					bigAstroidArr[ba2].addHit();
				}
			}
		}
		for (int ma = 0; ma < medAstroidIndex; ma++) {
			if (bigAstroidArr[ba].checkColl(&medAstroidArr[ma], tDelta)) {
				bigAstroidArr[ba].addHit();
				medAstroidArr[ma].addHit();
			}
		}

		for (int sa = 0; sa < smallAstroidIndex; sa++) {
			if (bigAstroidArr[ba].checkColl(&smallAstroidArr[sa], tDelta)) {
				bigAstroidArr[ba].addHit();
				smallAstroidArr[sa].addHit();
			}
		}
	}


	for (int ma = 0; ma < medAstroidIndex; ma++) {
		medAstroidArr[ma].updateVel(tDelta);
		medAstroidArr[ma].keepOnScreen(width / 2.0f, height / 2.0f);

		for (int ma2 = 0; ma2 < medAstroidIndex; ma2++) {
			if (ma != ma2) {
				if (medAstroidArr[ma].checkColl(&medAstroidArr[ma2], tDelta)) {
					medAstroidArr[ma].addHit();
					medAstroidArr[ma2].addHit();
				}
			}
		}
		for (int sa = 0; sa < smallAstroidIndex; sa++) {
			if (medAstroidArr[ma].checkColl(&smallAstroidArr[sa], tDelta)) {
				medAstroidArr[ma].addHit();
				smallAstroidArr[sa].addHit();
			}
		}
	}

	for (int sa = 0; sa < smallAstroidIndex; sa++) {
		smallAstroidArr[sa].updateVel(tDelta);
		smallAstroidArr[sa].keepOnScreen(width / 2.0f, height / 2.0f);

		
		for (int sa2 = 0; sa2 < smallAstroidIndex; sa2++) {
			if (sa != sa2) {
				if (smallAstroidArr[sa].checkColl(&smallAstroidArr[sa2], tDelta)) {
					smallAstroidArr[sa].addHit();
					smallAstroidArr[sa2].addHit();
				}
			}
		}
	}
}

void updateBullets(double tDelta) {

	// For every bullet in the array
	for (int i = 0; i < bulletIndex; i++) {

		// Update its position
		bullet[i].updateVel(tDelta);

		// If the bullet is off screen, delete it
		if (!bullet[i].deleteOffScreen(width / 2.0f, height / 2.0f)) {
			//do nothing
		}
		else {
			deleteBulletFromArray(bullet, i, &bulletIndex);

		}
		// Setup variables to check if the bullet hit an asteroid
		glm::vec2 hitPos;
		bool hit = false;
		bool kill = false;

		// For each UFO in the array
		for (int ufo = 0; ufo < ufoIndex; ufo++) {

			

			// If the bullet hit the UFO
			if (UFO[ufo].checkColl(&bullet[i], tDelta)) {

				// Get the position the hit happened
				hitPos = UFO[ufo].getPos();
				
				// Hit occured
				hit = true;

				// Reduce the UFOs healt
				if (UFO[ufo].reduceHealth()) {

					// If health == 0, delete the UFO.
					deleteUFO(ufo);
					kill = true;
					score += 10;
				}

				break;
			}
		}

		// for every asteroid (this setup applies for all asteroids)
		for (int ba = 0; ba < bigAstroidIndex; ba++) {

			// If the bullets already hit something, skip the rest of this loop
			if (hit) break;

			// If the bullet hit the asteroid
			if (bigAstroidArr[ba].checkColl(&bullet[i], tDelta)) {

				// Hit occured
				hit = true;

				// Get ths position of the hit
				hitPos = bigAstroidArr[ba].getPos();

				// Reduce the asteroids health.
				if (bigAstroidArr[ba].addHit()) {

					score += 5;
					//if health == 0; spawn spaller asteroids (only aplicable for big and med asteroids)
					spawnMedAstroid(tDelta, bigAstroidArr[ba].getPos());
					spawnMedAstroid(tDelta, bigAstroidArr[ba].getPos());

					// Reset the asteroids values
					bigAstroidArr[ba].makeNew(new Astroid());

					// delete the asteroid
					deleteFromAstroidArray(bigAstroidArr, ba, &bigAstroidIndex);

					// Bullet kill
					kill = true;
				}
			}
		}

		for (int ma = 0; ma < medAstroidIndex; ma++) {

			if (hit) break;

			if (medAstroidArr[ma].checkColl(&bullet[i], tDelta)) {

				hit = true;

				hitPos = medAstroidArr[ma].getPos();

				if (medAstroidArr[ma].addHit()) {

					score += 2;

					spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());
					spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());
					spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());

					medAstroidArr[ma].makeNew(new Astroid());

					deleteFromAstroidArray(medAstroidArr, ma, &medAstroidIndex);

					kill = true;
				}
			}
		}

		for (int sa = 0; sa < smallAstroidIndex; sa++) {

			if (hit) break;

			if (smallAstroidArr[sa].checkColl(&bullet[i], tDelta)) {

				hit = true;

				hitPos = smallAstroidArr[sa].getPos();

				if (smallAstroidArr[sa].addHit()) {

					score += 1;

					smallAstroidArr[sa].makeNew(new Astroid());

					deleteFromAstroidArray(smallAstroidArr, sa, &smallAstroidIndex);

					kill = true;
				}
			}
		}

		// If a hit occured, delete the bullet
		if (hit) {
			deleteBulletFromArray(bullet, i, &bulletIndex);
		}

		// If a kill occured 
		if (kill) {
			
			// Check if the health postion is already active (only one at a time), the following applies for all power ups.
			if (healthUp.getPos().x < 100) {
				//do nothing
			}
			else {
				int chance = rand() % 100 + 1;
				// 2% chance to spawn the health power up
				if (chance < 3) {

					// Spawn the power up
					spawnPUp(&healthUp, hitPos);

					// Set the despawn timer to 0
					healthUpTimer = 0;
				}
			}

			if (shieldUp.getPos().x < 100) {
				//do nothing
			}
			else {
				int chance = rand() % 100 + 1;
				if (chance < 2) {

					spawnPUp(&shieldUp, hitPos);

					shieldUpTimer = 0;
				}
			}

			if (fireRateUp.getPos().x < 100.0f) {
				// do nothing
			}
			else {
				int chance = rand() % 100 + 1;
				if (chance < 2) {

					spawnPUp(&fireRateUp, hitPos);

					fireRateTimer = 0;
				}
			}

			if (trippleShot.getPos().x < 100.0f) {
				// do nothing
			}
			else {
				int chance = rand() % 100 + 1;

				if (chance < 2) {
					
					spawnPUp(&trippleShot, hitPos);

					trippleShotTimer = 0;
				}
			}
			if (clover.getPos().x < 100.0f) {
				// do nothing
			}
			else {
				int chance = rand() % 700 + 1;

				if (chance < 2) {

					spawnPUp(&clover, hitPos);

					cloverDespawnTimer = 0;
				}
			}
			
		}
	}
}

void ufoUpdateBullets(double tDelta) {
	// For every UFO bullet
	for (int i = 0; i < enemyBulletIndex; i++) {

		// Check if bullet is on screen
		if (!enemyBullet[i].deleteOffScreen(width / 2.0f, height / 2.0f)) {
			//do nothing
		}
		else {

			// If its off screen, delete it
			deleteBulletFromArray(enemyBullet, i, &enemyBulletIndex);
		}

		// Check if the bullet hit the player
		if (enemyBullet[i].checkColl(player, tDelta)) {

			// If it did, reduce player health
			if (player->reduceHealth()) {

				
			}

			// Delete the bullet if it hit the player
			deleteBulletFromArray(enemyBullet, i, &enemyBulletIndex);
		}

		// Update the bullets position
		enemyBullet[i].updateVel(tDelta);
	}
}

void updateAnim(double tDelta) {
	// Get players position and offset it forwards
	float fX = 5 * cos(player->getOri()) + player->getPos().x;
	float fY = 5 * sin(player->getOri()) + player->getPos().y;

	// Offset the position to the left and right respectivly 
	float lX = fX + (2 * cos(player->getOri() + 90 * 180 / PI));
	float lY = fY + (2 * sin(player->getOri() + 90 * 180 / PI));

	float rX = fX + (2 * cos(player->getOri() - 90 * 180 / PI));
	float rY = fY + (2 * sin(player->getOri() - 90 * 180 / PI));

	// Update the Animations, using its position relitive to the player
	gunFlareAnimL.updateAnim(tDelta, glm::vec2(lX,lY), player->getOri());
	gunFlareAnimR.updateAnim(tDelta, glm::vec2(rX,rY), player->getOri());
}

void updateUps(double tDelta) {
	// Only update the power up if its in bounds (in use), the following applies for all power ups
	if (healthUp.getPos().x < 100) {

		// Update the positition and keep it on screen
		healthUp.updateVel(tDelta);
		healthUp.keepOnScreen(width / 2.0f, height / 2.0f);

		// Increment the despawn timer
		healthUpTimer += (float) tDelta;

		if (healthUpTimer > powerUpDespawn) {
			// If the timer is up, move the power up out of bounds
			healthUp.setPos(glm::vec2(1000.0f, 1000.0f));
		}
	}
	else {
		//do nothing
	}

	if (clover.getPos().x < 100) {

		// Update the positition and keep it on screen
		clover.updateVel(tDelta);
		clover.keepOnScreen(width / 2.0f, height / 2.0f);

		// Increment the despawn timer
		cloverDespawnTimer += (float)tDelta;

		if (cloverDespawnTimer > powerUpDespawn) {
			// If the timer is up, move the power up out of bounds
			clover.setPos(glm::vec2(1000.0f, 1000.0f));
		}
	}
	else {
		//do nothing
	}

	

	// Only update the power up if its in bounds (in use), the following applies for all power ups
	if (trippleShot.getPos().x < 100) {

		// Update the positition and keep it on screen
		trippleShot.updateVel(tDelta);
		trippleShot.keepOnScreen(width / 2.0f, height / 2.0f);

		// Increment the despawn timer
		trippleShotTimer += (float)tDelta;

		if (trippleShotTimer > powerUpDespawn) {
			// If the timer is up, move the power up out of bounds
			healthUp.setPos(glm::vec2(1000.0f, 1000.0f));

		}
	}
	else {
		//do nothing
	}


	if (shieldUp.getPos().x < 100) {

		shieldUp.updateVel(tDelta);
		shieldUp.keepOnScreen(width / 2.0f, height / 2.0f);

		shieldUpTimer += (float) tDelta;

		if (shieldUpTimer > powerUpDespawn) {

			shieldUp.setPos(glm::vec2(1000.0f, 1000.0f));
		}
	}
	else {
		//do nothing
	}

	if (fireRateUp.getPos().x < 100) {

		fireRateUp.updateVel(tDelta);
		fireRateUp.keepOnScreen(width / 2.0f, height / 2.0f);

		fireRateTimer += (float) tDelta;

		if (fireRateTimer > powerUpDespawn) {

			fireRateUp.setPos(glm::vec2(1000.0f, 1000.0f));
		}
	}
	else {
		// do nothing
	}

	if (boostedDelayTimer > 0) {

		boostedDelayTimer -= (float)tDelta;
	} 
	else if (boostedDelayTimer < 0) {
		shotDelay = stdDelay;
	}
	else
	{
		// do nothing
	}

	if (hasTrippleShot) {
		trippleShotLen -= (float)tDelta;
		if (trippleShotLen < 0) {
			hasTrippleShot = false;
		}
	}

	if (boostedDelayTimer2 > 0) {

		boostedDelayTimer2 -= (float)tDelta;
	}
	else if (boostedDelayTimer2 < 0) {
		shotDelay2 = stdDelay;
	}
	else
	{
		// do nothing
	}

	if (hasTrippleShot2) {
		trippleShotLen2 -= (float)tDelta;
		if (trippleShotLen2 < 0) {
			hasTrippleShot2 = false;
		}
	}
}

// Check players colisions
void checkPlayerHB(double tDelta) {

	if (healthUp.getPos().x < 100.0f) {
		// Check the players colision on power ups
		if (healthUp.checkColl(player, tDelta)) {
			// If its a hit, move the power up out of bounds
			healthUp.setPos(glm::vec2(1000.0f, 1000.0f));

			// Add health to the player
			player->addHealth();
		}
		if (healthUp.checkColl(player2, tDelta)) {
			// If its a hit, move the power up out of bounds
			healthUp.setPos(glm::vec2(1000.0f, 1000.0f));

			// Add health to the player
			player2->addHealth();
		}
	}

	if (clover.getPos().x < 100.0f) {
		// Check the players colision on power ups
		if (clover.checkColl(player, tDelta)) {

			spawnPUp(&fireRateUp, clover.getPos());
			spawnPUp(&trippleShot, clover.getPos());
			spawnPUp(&shieldUp, clover.getPos());
			spawnPUp(&healthUp, clover.getPos());

			clover.setPos(glm::vec2(1000.0f, 1000.0f));
		}
		if (clover.checkColl(player2, tDelta)) {

			spawnPUp(&fireRateUp, clover.getPos());
			spawnPUp(&trippleShot, clover.getPos());
			spawnPUp(&shieldUp, clover.getPos());
			spawnPUp(&healthUp, clover.getPos());

			clover.setPos(glm::vec2(1000.0f, 1000.0f));
		}
	}

	if (trippleShot.getPos().x < 100.0f) {
		if (trippleShot.checkColl(player, tDelta)) {
			trippleShot.setPos(glm::vec2(1000.0f,100.0f));


			trippleShotLen = boostedShotLen;

			hasTrippleShot = true;
		}

		if (trippleShot.checkColl(player2, tDelta)) {
			trippleShot.setPos(glm::vec2(1000.0f, 100.0f));


			trippleShotLen2 = boostedShotLen;

			hasTrippleShot2 = true;
		}
	}
	if (shieldUp.getPos().x < 100.0f) {
		if (shieldUp.checkColl(player, tDelta)) {

			shieldUp.setPos(glm::vec2(1000.0f, 1000.0f));

			// Add a sheild to the player
			player->addSheild();
		}
		if (shieldUp.checkColl(player2, tDelta)) {

			shieldUp.setPos(glm::vec2(1000.0f, 1000.0f));

			// Add a sheild to the player
			player2->addSheild();
		}
	}

	if (fireRateUp.getPos().x < 100.0f) {
		if (fireRateUp.checkColl(player, tDelta)) {

			fireRateUp.setPos(glm::vec2(1000.0f,1000.0f));

			shotDelay = boostedDelay;
			boostedDelayTimer = boostedShotLen;
		}
		if (fireRateUp.checkColl(player2, tDelta)) {

			fireRateUp.setPos(glm::vec2(1000.0f, 1000.0f));

			shotDelay2 = boostedDelay;
			boostedDelayTimer2 = boostedShotLen;
		}
	}

	// Increment the damage cooldown
	cDamageTimer2 += (float) tDelta;

	
	// Increment the damage cooldown
	cDamageTimer += (float) tDelta;

	// create boolean for a hit
	bool hit = false;
	bool hit2 = false;
	
	glm::vec2 playerPos = player->getPos();

	// For every ufo in the scene (this works the same with asteroids)
	for (int ufo = 0; ufo < ufoIndex; ufo++) {

		// Check if the player hit it
		if (player->checkColl(&UFO[ufo], tDelta)) {

			hit = true;

			// Reduce the UFOs healt
			if (UFO[ufo].reduceHealth()) {

				// If health == 0, delete the UFO.
				deleteUFO(ufo);
				score += 10;
			}
		}

		// Check if the player hit it
		if (player2->checkColl(&UFO[ufo], tDelta)) {

			hit2 = true;

			// Reduce the UFOs healt
			if (UFO[ufo].reduceHealth()) {

				// If health == 0, delete the UFO.
				deleteUFO(ufo);
				score += 10;
			}
		}
	}
	for (int ba = 0; ba < bigAstroidIndex; ba++) {

		// If somethings already been hit, skip
		if (hit || hit2) break;

		if (player->checkColl(&bigAstroidArr[ba], tDelta)) {

			hit = true;

			// Reduce the asteroids health.
			if (bigAstroidArr[ba].addHit()) {

				score += 5;
				//if health == 0; spawn spaller asteroids (only aplicable for big and med asteroids)
				spawnMedAstroid(tDelta, bigAstroidArr[ba].getPos());
				spawnMedAstroid(tDelta, bigAstroidArr[ba].getPos());

				// Reset the asteroids values
				bigAstroidArr[ba].makeNew(new Astroid());

				// delete the asteroid
				deleteFromAstroidArray(bigAstroidArr, ba, &bigAstroidIndex);
			}
		}

		if (player2->checkColl(&bigAstroidArr[ba], tDelta)) {

			hit2 = true;

			// Reduce the asteroids health.
			if (bigAstroidArr[ba].addHit()) {

				score += 5;
				//if health == 0; spawn spaller asteroids (only aplicable for big and med asteroids)
				spawnMedAstroid(tDelta, bigAstroidArr[ba].getPos());
				spawnMedAstroid(tDelta, bigAstroidArr[ba].getPos());

				// Reset the asteroids values
				bigAstroidArr[ba].makeNew(new Astroid());

				// delete the asteroid
				deleteFromAstroidArray(bigAstroidArr, ba, &bigAstroidIndex);
			}
		}
	}

	for (int ma = 0; ma < medAstroidIndex; ma++) {

		if (hit || hit2) break;

		if (player->checkColl(&medAstroidArr[ma], tDelta)) {

			hit = true;

			// Reduce the asteroids health.
			if (medAstroidArr[ma].addHit()) {

				score += 5;
				//if health == 0; spawn spaller asteroids (only aplicable for big and med asteroids)
				spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());
				spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());
				spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());

				// Reset the asteroids values
				medAstroidArr[ma].makeNew(new Astroid());

				// delete the asteroid
				deleteFromAstroidArray(medAstroidArr, ma, &medAstroidIndex);
			}
		}

		if (player2->checkColl(&medAstroidArr[ma], tDelta)) {

			hit2 = true;

			// Reduce the asteroids health.
			if (medAstroidArr[ma].addHit()) {

				score += 5;
				//if health == 0; spawn spaller asteroids (only aplicable for big and med asteroids)
				spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());
				spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());
				spawnSmallAstroid(tDelta, medAstroidArr[ma].getPos());

				// Reset the asteroids values
				medAstroidArr[ma].makeNew(new Astroid());

				// delete the asteroid
				deleteFromAstroidArray(medAstroidArr, ma, &medAstroidIndex);
			}
		}
	}

	for (int sa = 0; sa < smallAstroidIndex; sa++) {

		if (hit || hit2) break;

		if (player->checkColl(&smallAstroidArr[sa], tDelta)) {

			hit = true;

			// Reduce the asteroids health.
			if (smallAstroidArr[sa].addHit()) {

				score += 5;

				// Reset the asteroids values
				smallAstroidArr[sa].makeNew(new Astroid());

				// delete the asteroid
				deleteFromAstroidArray(smallAstroidArr, sa, &smallAstroidIndex);
			}
		}
		if (player2->checkColl(&smallAstroidArr[sa], tDelta)) {

			hit2 = true;

			// Reduce the asteroids health.
			if (smallAstroidArr[sa].addHit()) {

				score += 5;

				// Reset the asteroids values
				smallAstroidArr[sa].makeNew(new Astroid());

				// delete the asteroid
				deleteFromAstroidArray(smallAstroidArr, sa, &smallAstroidIndex);
			}
		}
	}

	// If the player has been hit
	if (hit) {
		if (cDamageTimer > damageCoolDown) {
			// Reset the damage cool down timer.
			cDamageTimer = 0.0f;

			// If player health = 0;
			if (player->reduceHealth()) {


			}
		}
	}

	if (hit2) {
		if (cDamageTimer2 > damageCoolDown) {
			// Reset the damage cool down timer.
			cDamageTimer2 = 0.0f;

			// If player health = 0;
			if (player2->reduceHealth()) {


			}
		}
	}

}

// Check level win condition
void checkCompletion() {

	// If there are no asteroids or ufos left.
	if (bigAstroidIndex + medAstroidIndex + smallAstroidIndex + ufoIndex == 0 && levelInProgress) {

		// Reset level delay (makes levels take some time to spawn)
		cLevelDelay = 0.0f;

		// Reset level in prog bool so that spawnLevel() can spawn a new level
		levelInProgress = false;

		// If the current level is not the max level
		if (currentLevel != maxLevel) {

			// Go to next level
			currentLevel++;
		}
	}
}

// Spawn new level
void spawnLevel(double tDelta) {

	// If theres a level in progress, or the level spawn delay isnt over
	if (levelInProgress || cLevelDelay < levelDelay) {

		// increment the lvel delay, and return
		cLevelDelay += (float) tDelta;
		return;
	// if a level is not in progress, and the level delay is over
	} else {

		// A level is in progress
		levelInProgress = true;

		// Clear unused objects before spawning a level
		clearScene(); 

		// The following applies for all asteroids
		// For every big astroid that needs to be spawned (eg, level 10 with 1 big asteroid per level = iterate 10 times)
		for (int ba = 0; ba < baPerLevel * currentLevel; ba++) {

			// Declare the x and y position the asteroid will spawn at
			float xPos = 0;
			float yPos = 0;

			// Random number to decide if the asteroid will spawn at the top of the screen, or at the bottom.
			if (rand() % 2 < 1) {

				// create a random X value
				xPos = rand() % (int)width - width / 2.0f;

				// X pos is the top of the view
				yPos = height / 2.0f + 10.0f;
			}
			else {

				// create a random Y value
				yPos = rand() % (int)height - height / 2.0f;

				// X pos is the right side of the view
				xPos = width / 2.0f + 10.0f;
			}

			// Note that the random orientation of the asteroid decideds if it will spawn at the top or bottom / left or right, so no need to randomise that 

			// Spawn the asteroid
			spawnBigAstroid(tDelta, glm::vec2(xPos, yPos));
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

			spawnMedAstroid(tDelta, glm::vec2(xPos, yPos));
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

			spawnSmallAstroid(tDelta, glm::vec2(xPos, yPos));
		}

		// For every ufo in the current level
		for (int ufo = 0; ufo < (int) (ufoPerLevel * currentLevel); ufo++) {
			// Declare the position variables
			float xPos = 0;
			float yPos = 0;

			// The Y pos is randomised, and set to any value above the centre of the view
			yPos = rand() % (int)height/2.0f;

			// The X value is set to the side of the view
			xPos = width / 2.0f + 10.0f;

			// Spawn the UFO.
			spawnUFO(tDelta, glm::vec2(xPos, yPos));
		}
	}
}

// Spawn object functions

// The following applies for all asteroids
void spawnBigAstroid(double tDelta, glm::vec2 pos) {

	// Set a random orientation between 0 and 259 degrees.
	float ori = glm::radians(rand() % 360 * 1.0f);

	// Set a random rotation speed between 50 and 120 
	float rotSpeed = rand() % 50 + 70 * 1.0f;

	// Decide if the rotation speed will be clockwise or anticlockwise
	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	// Create a random size between 28 and 33
	int size = rand() % 5 + 28;

	// Create a new asteroid in the array
	bigAstroidArr[bigAstroidIndex].makeNew(Astroid(pos, ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 0));

	// Set the asteroids velocity
	bigAstroidArr[bigAstroidIndex].setVelocity(bigAstroidArr[bigAstroidIndex].getForwardVector(), bigAstroidSpeed);

	// Increment the asteroid index.
	bigAstroidIndex++;
}

void spawnMedAstroid(double tDelta, glm::vec2 pos) {

	float ori = glm::radians(rand() % 360 * 1.0f);

	float rotSpeed = rand() % 50 + 100 * 1.0f;

	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	int size = rand() % 5 + 18;

	medAstroidArr[medAstroidIndex].makeNew(Astroid(pos, ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 1));

	medAstroidArr[medAstroidIndex].setVelocity(medAstroidArr[medAstroidIndex].getForwardVector(), medAstroidSpeed);

	medAstroidIndex++;
}

void spawnSmallAstroid(double tDelta, glm::vec2 pos) {

	float ori = glm::radians(rand() % 360 * 1.0f);

	float rotSpeed = rand() % 50 + 140 * 1.0f;

	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	int size = rand() % 5 + 8;

	smallAstroidArr[smallAstroidIndex].makeNew(Astroid(pos, ori, astroidBigTexture, glm::vec2(size, size), glm::radians(rotSpeed), 2));

	smallAstroidArr[smallAstroidIndex].setVelocity(smallAstroidArr[smallAstroidIndex].getForwardVector(), smallAstroidSpeed);

	smallAstroidIndex++;
}

void spawnBackgrounfParticles(double tDelta, glm::vec2 pos, int index) {

	float ori = glm::radians(rand() % 360 * 1.0f);

	float rotSpeed = rand() % 50 + 100 * 1.0f;

	if (rand() % 2 < 1) {
		rotSpeed *= -1.0f;
	}

	float size = (rand() % 100)/180.0f;

	float speed = rand() % 20 + 5;

	backgroundParticles[index].makeNew(Astroid(pos, ori, startText, glm::vec2(size, size), glm::radians(rotSpeed), 1));

	backgroundParticles[index].setVelocity(backgroundParticles[index].getForwardVector(), speed);
}

void spawnUFO(double tDelta, glm::vec2 pos) {
	// Create a random speed between  47 and 53
	float speed = rand() % 6 + ufoSpeed - 3;

	// Decide if the UFO will scroll left or right
	if (rand() % 2 < 1) {
		speed = -speed;
	}
	// Create the UFOs muzzle flash Animation
	UFOgunFlare[ufoIndex].makeNew(Animation(0.0f, blueGunFlareIDs, 4, glm::vec2(3, 3)));

	// Create the new UFO
	UFO[ufoIndex].makeNew(EnemyUFO(pos, 0, UFOtexture, glm::vec2(10.0f, 10.0f), &UFOgunFlare[ufoIndex]));

	// Apply the UFOs velocity
	UFO[ufoIndex].setVelocity(UFO[ufoIndex].getForwardVector(), speed);

	// Incerement to UFO index
	ufoIndex++;
}

void spawnPUp(GameObject* powerUp, glm::vec2 pos) {
	// Create a random direction for movement
	float ori = glm::radians(rand() % 360 * 1.0f);

	// Set this direction
	powerUp->setOri(ori);

	// Apply the velocity in the random direction
	powerUp->setVelocity(powerUp->getForwardVector(), pUpSpeed);

	// Set the position of the power up to its spawn position
	powerUp->setPos(pos);

	// Reset the orientation to 0.
	powerUp->setOri(0);

}

// Update UFOs
void enemyControl(double tDelta) {
	// For every UFO in the array
	for (int i = 0; i < ufoIndex; i++) {

		// Get its x value
		float fX = UFO[i].getPos().x;

		// Get its Y value and offset it down
		float fY = UFO[i].getPos().y - 2.5f;

		// update the Animation at the new position
		UFO[i].updateAnim(tDelta, glm::vec2(fX,fY), UFO[i].getOri());

		// Add to the shot delay
		UFO[i].addToTimer(tDelta);

		// If the UFO can shoot
		if (UFO[i].getTimer() > ufoShotDelay) {
			// Shoot
			enemyShoot(tDelta, i);

			// Reset the shot timer
			UFO[i].setTimer(0.0f);
		}
		// Update the velocity, and keep the UFO on screen
		UFO[i].updateVel(tDelta);
		UFO[i].keepOnScreen(width / 2.0f, height / 2.0f);
	}
}

// Control the player
void playerControl(double tDelta) {

	// Add to the shot delay
	shotTimer += (float) tDelta;

	// Decide if the player can shoot or not
	if (shotTimer > shotDelay) {
		canShoot = true;
	}

	// Do the corisponding control depending on what key is being pressed
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
	}

	if (leftShift) {
		glm::vec2 velocity = player->getVel();
		if (glm::length(velocity) > 0) {

			glm::vec2 velDir = glm::normalize(player->getVel());
			player->addVelocity(velDir, forwardForce * -1.0, tDelta);
		}
	}

	// If the user is shooting, and the player can shoot
	if (spaceKey && canShoot) {
		// Shoot
		shoot(tDelta);

		// Reset the shot timer
		shotTimer = 0.0f;
	}
	
	// Update the players position
	player->update(tDelta);

	// Add to the shot delay
	shotTimer2 += (float)tDelta;

	// Decide if the player can shoot or not
	if (shotTimer2 > shotDelay2) {
		canShoot2 = true;
	}

	// Do the corisponding control depending on what key is being pressed
	if (key4) {
		player2->turnLeft(tDelta);
	}

	if (key6) {
		player2->turnRight(tDelta);
	}

	if (key8) {
		player2->addVelocity(player2->getForwardVector(), forwardForce, tDelta);
	}

	if (key5) {
		player2->addVelocity(player2->getForwardVector(), forwardForce * -1.0, tDelta);
	}

	if (downKey) {
		glm::vec2 velocity = player2->getVel();
		if (glm::length(velocity) > 0) {

			glm::vec2 velDir = glm::normalize(player2->getVel());
			player2->addVelocity(velDir, forwardForce * -1.0, tDelta);
		}
	}

	// If the user is shooting, and the player can shoot
	if (rightKey && canShoot2) {
		// Shoot
		shoot2(tDelta);

		// Reset the shot timer
		shotTimer2 = 0.0f;
	}

	// Update the players position
	player2->update(tDelta);
}

// clear scene (clear objects from the engine)
void clearScene() {
	// Delete all bullets
	bullet = new Bullet[maxBul];
	bulletIndex = 0;

	enemyBullet = new Bullet[maxEnemyBul];
	enemyBulletIndex = 0;

	// Delete all big asteroids
	bigAstroidArr = new Astroid[maxBAs];
	bigAstroidIndex = 0;

	// Delete all medium asteroids
	medAstroidArr = new Astroid[maxMAs];
	medAstroidIndex = 0;

	// Delete all small asteroids
	smallAstroidArr = new Astroid[maxSAs];
	smallAstroidIndex = 0;

	// Delete all UFOs
	UFO = new EnemyUFO[maxUFO];
	ufoIndex = 0;
}

// Reset players health and position, and clear the scene
void fullReset() {
	player->alive = true;
	player2->alive = true;
	std::cout << "Your final score was: " << score << std::endl;

	score = 0;
	// Reset level 
	currentLevel = 1;
	levelInProgress = false;

	// Clear the scene
	clearScene();

	// Reset player position
	player->setPos(glm::vec2(0,0));

	// Reset player position
	player2->setPos(glm::vec2(0, 0));

	// Reset power up positions
	healthUp.setPos(glm::vec2(1000.0f, 1000.0f));
	shieldUp.setPos(glm::vec2(1000.0f, 1000.0f));
	fireRateUp.setPos(glm::vec2(1000.0f, 1000.0f));
	clover.setPos(glm::vec2(1000.0f, 1000.0f));
	trippleShot.setPos(glm::vec2(1000.0f, 1000.0f));

	// Set player to full health
	player->setFullHealth();

	// Remove players velocity
	player->resetVel();


	// Set player to full health
	player2->setFullHealth();

	// Remove players velocity
	player2->resetVel();
}

// delete objects from array

// The following applies to all delete functions
void deleteUFO(int index) {

	// move the shoot Animation off screen
	UFO[index].getAnim()->setPos(glm::vec2(1000.0f, 1000.0f));

	// For every object starting at the current index
	for (int i = index; i < ufoIndex - 1; i++) {

		// Shift the following object to the current index
		UFO[i].makeNew(UFO[i + 1]);
	}

	// Remove 1 from the index
	ufoIndex--;

	// Reset the last UFO and move it out of bounds
	UFO[ufoIndex].makeNew(EnemyUFO());
	UFO[ufoIndex].setPos(glm::vec2(1000.0f, 1000.0f));
}

void deleteBulletFromArray(Bullet* array, int index, int* arrSize) {
	
	for (int i = index; i < (*arrSize) - 1; i++) {

		
		array[i].makeNew(array[i + 1]);
	}

	if ((*arrSize) != 0) {
		(*arrSize)--;
	}

	array[*arrSize].makeNew(Bullet());

	array[*arrSize].setPos(glm::vec2(1000.0f, 1000.0f));
}

void deleteFromAstroidArray(Astroid* array, int index, int* arrSize) {
	
	for (int i = index; i < (*arrSize) - 1; i++) {

		array[i].makeNew(array[i + 1]);
	}

	(*arrSize)--;

	array[*arrSize].makeNew(Astroid());
	array[*arrSize].setPos(glm::vec2(1000.0f, 1000.0f));
}

// shoot functions
void enemyShoot(double tDelta, int index) {
	// Create a new enemy bullet
	enemyBullet[enemyBulletIndex].makeNew(UFO[index].shoot(tDelta, bulletMag, ufoBulletText, BulletSize));

	// Apply its velocity
	enemyBullet[enemyBulletIndex].setVelocity(enemyBullet[enemyBulletIndex].getForwardVector(), bulletMag);



	// Increment the enemy Bullet index
	enemyBulletIndex++;
}

void shoot(double tDelta) {
	// Set can shoot to false
	canShoot = false;

	// Create a new bullet
	bullet[bulletIndex].makeNew(player->shoot(tDelta, bulletMag, bulletTexture, BulletSize,&gunFlareAnimL,&gunFlareAnimR, 0));

	// Set its velocity
	bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

	// Inceremnt the bullet index.
	bulletIndex++;

	if (hasTrippleShot) {
		// Create a new bullet
		bullet[bulletIndex].makeNew(player->shoot(tDelta, bulletMag, bulletTexture, BulletSize, &gunFlareAnimL, &gunFlareAnimR, glm::radians(30.0f)));

		// Set its velocity
		bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

		// Inceremnt the bullet index.
		bulletIndex++;

		// Create a new bullet
		bullet[bulletIndex].makeNew(player->shoot(tDelta, bulletMag, bulletTexture, BulletSize, &gunFlareAnimL, &gunFlareAnimR, glm::radians(-30.0f)));

		// Set its velocity
		bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

		// Inceremnt the bullet index.
		bulletIndex++;
	}
}

void shoot2(double tDelta) {
	// Set can shoot to false
	canShoot2 = false;

	// Create a new bullet
	bullet[bulletIndex].makeNew(player2->shoot(tDelta, bulletMag, bulletTexture, BulletSize, &gunFlareAnimL2, &gunFlareAnimR2, 0));

	// Set its velocity
	bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

	// Inceremnt the bullet index.
	bulletIndex++;

	if (hasTrippleShot2) {
		// Create a new bullet
		bullet[bulletIndex].makeNew(player2->shoot(tDelta, bulletMag, bulletTexture, BulletSize, &gunFlareAnimL2, &gunFlareAnimR2, glm::radians(30.0f)));

		// Set its velocity
		bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

		// Inceremnt the bullet index.
		bulletIndex++;

		// Create a new bullet
		bullet[bulletIndex].makeNew(player2->shoot(tDelta, bulletMag, bulletTexture, BulletSize, &gunFlareAnimL2, &gunFlareAnimR2, glm::radians(-30.0f)));

		// Set its velocity
		bullet[bulletIndex].setVelocity(bullet[bulletIndex].getForwardVector(), bulletMag);

		// Inceremnt the bullet index.
		bulletIndex++;
	}
}

// Custom render fucntion
void myRenderFunction(GLFWwindow* window) {

	background.render();

	for (int i = 0; i < 50; i++) {
		backgroundParticles[i].render();
	}

	earth.render();

	// render every single game object
	player->render();
	player2->render();

	if (player->getShield()->getPos().x < 100) {
		player->getShield()->render();
	}

	if (healthUp.getPos().x < 100) {
		healthUp.render();
	}

	if (shieldUp.getPos().x < 100) {
		shieldUp.render();
	}

	if (fireRateUp.getPos().x < 100.0f) {
		fireRateUp.render();
	}

	if (trippleShot.getPos().x < 100.0f) {
		trippleShot.render();
	}

	if (clover.getPos().x < 100.0f) {
		clover.render();
	}

	for (int i = 50; i < 75; i++) {
		backgroundParticles[i].render();
	}
	
	for (int i = 0; i < bulletIndex; i++) {
		bullet[i].render();
	}

	for (int i = 0; i < smallAstroidIndex; i++) {
		smallAstroidArr[i].render();
	}

	for (int i = 0; i < medAstroidIndex; i++) {
		medAstroidArr[i].render();
	}

	for (int i = 0; i < bigAstroidIndex; i++) {
		bigAstroidArr[i].render();
	}

	for (int i = 0; i < ufoIndex; i++) {
		UFO[i].render();
		UFO[i].getAnim()->render();
	}

	for (int i = 0; i < enemyBulletIndex; i++) {
		enemyBullet[i].render();
	}

	if (gunFlareAnimL.getPos().x < 100) {
		gunFlareAnimL.render();
	}

	if (gunFlareAnimR.getPos().x < 100) {
		gunFlareAnimR.render();
	}

	for (int i = 75; i < 100; i++) {
		backgroundParticles[i].render();
	}

	player->getHB()->render();
	player2->getHB()->render(); 
}

void releaseMemory() {
	delete[] bigAstroidArr;
	delete[] medAstroidArr;
	delete[] smallAstroidArr;
	delete[] bullet;
	delete[] enemyBullet;
	delete[] UFO;
	delete[] blueGunFlareIDs;
	delete[] gunFlareIDs;
	delete[] UFOgunFlare;
	delete[] healthTextIDs;
	delete player;
}

//Keyboard handler
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if a key is pressed
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// if escape was pressed
			
			// Clear the the memory
			releaseMemory();

			// Close the window
			glfwSetWindowShouldClose(window, true);
			break;

		// For the rest, set the corosponding boolian to true
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
		case GLFW_KEY_LEFT_SHIFT:
			leftShift = true;
			break;
		case GLFW_KEY_KP_8:
			key8 = true;
			break;
		case GLFW_KEY_KP_4:
			key4 = true;
			break;
		case GLFW_KEY_KP_5:
			key5 = true;
			break;
		case GLFW_KEY_KP_6:
			key6 = true;
			break;
		case GLFW_KEY_RIGHT:
			rightKey = true;
			break;
		case GLFW_KEY_DOWN:
			downKey = true;
			break;
		case GLFW_KEY_P:
			printf("stoppoint");
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

		// If the key was released, set its boolean to false.
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
		case GLFW_KEY_LEFT_SHIFT:
			leftShift = false;
			break;
		case GLFW_KEY_KP_8:
			key8 = false;
			break;
		case GLFW_KEY_KP_4:
			key4 = false;
			break;
		case GLFW_KEY_KP_5:
			key5 = false;
			break;
		case GLFW_KEY_KP_6:
			key6 = false;
			break;
		case GLFW_KEY_RIGHT:
			rightKey = false;
			break;
		case GLFW_KEY_DOWN:
			downKey = false;
			break;
		default:
		{
		}
		}
	}
}
