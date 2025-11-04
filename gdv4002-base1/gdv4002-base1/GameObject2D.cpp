#include "GameObject2D.h"
glm::vec2 GameObject2D::getPos() {
	return position;
}

void GameObject2D::setPos(glm::vec2 pos) {
	position = pos;
}

float GameObject2D::getOri() {
	return orientation;
}

void GameObject2D::setOri(float ori) {
	orientation = ori;
}

glm::vec2 GameObject2D::getSize() {
	return size;
}

void GameObject2D::setSize(glm::vec2 size) {
	this->size = size;
}

int GameObject2D::getTexture() {
	return textureID;
}

void GameObject2D::setTexture(int textureID) {
	this->textureID = textureID;
}

GameObject2D::GameObject2D() {
}

/*
Create new objects, Parms:

vec2 initPosition
vec2 initSize
GLunit initTextureID
*/
GameObject2D::GameObject2D(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID) {

	position = initPosition;
	orientation = initOrientation;
	size = initSize;
	textureID = initTextureID;
}

void GameObject2D::render() {

	// Render objects here...

	

	glPushMatrix();
	
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(glm::degrees(orientation), 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, 1.0f);

	if (textureID > 0) {

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);

		//We changed this for transparent texture backgrounds
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	glEnd();

	if (textureID > 0) {

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	glPopMatrix();
}

void GameObject2D::update(double tDelta) {}
