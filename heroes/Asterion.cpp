#include "Asterion.h"



void Asterion::drawSpoke() {
	glPushMatrix();
	glColor3f(0, 0, 0);					// black
	glScalef(3, 0.25, 0.25);
	glutSolidCube(1);
	glPopMatrix();
}

void Asterion::drawWheel() {
	glPushMatrix();
	glColor3f(0.24, 0.35, 0.67);				// blue
	glScalef(1, 1, 0.5);
	glutSolidTorus(1, 2, 50, 50);
	glPopMatrix();

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(0, 0, 0);
		glRotatef(i * 360 / 8, 0, 0, 1);
		drawSpoke();
		glPopMatrix();
	}
}

void Asterion::buildCar() {
	glPushMatrix();
	glColor3f(0.25, 0.41, 0.88);			// different blue
	glTranslatef(0, 3, 0);
	glScalef(24, 3, 6);
	glutSolidCube(1);
	glPopMatrix();

	// Wheels
	glPushMatrix();
	glTranslatef(8, 3, 3.5);
	glRotatef(wheelRotation, 0, 0, 1);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 3, -3.5);
	glRotatef(wheelRotation, 0, 0, 1);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 3.5);
	glRotatef(wheelRotation, 0, 0, 1);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, -3.5);
	glRotatef(wheelRotation, 0, 0, 1);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 3, 3.5);
	glRotatef(wheelRotation, 0, 0, 1);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 3, -3.5);
	glRotatef(wheelRotation, 0, 0, 1);
	drawWheel();
	glPopMatrix();

	// Front indicator
	glPushMatrix();
	glColor3f(0.23, 0.23, 0.23);			// grey
	glTranslatef(8, 5, 0);
	glRotatef(teapotRotation, 0, 1, 0);
	glutSolidTeapot(1);
	glPopMatrix();
}

void Asterion::move(float xIn, float yIn, float zIn) {
	x = xIn;
	y = yIn;
	z = zIn;
}

void Asterion::rotate(float thetaIn, float phiIn) {
	theta = thetaIn;
	phi = phiIn;
}

void Asterion::draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.4, 0.4, 0.4);
	glRotatef(theta * 180 / M_PI, 0, 1, 0);
	glRotatef(phi * 180 / M_PI, 0, 0, 1);
	buildCar();
	glPopMatrix();
}
