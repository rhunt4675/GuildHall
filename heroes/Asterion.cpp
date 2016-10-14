#include "Asterion.h"

void Asterion::drawSpoke() {
	glPushMatrix();
	cloth.setBlackPlastic();					// black
	glScalef(3, 0.25, 0.25);
	glutSolidCube(1);
	glPopMatrix();
}

void Asterion::drawWheel() {
	glPushMatrix();
	cloth.setTurquoise();				// blue
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
	cloth.setPearl();		// different blue
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
	cloth.setBrass();			// grey
	glTranslatef(8, 5, 0);
	glRotatef(teapotRotation, 0, 1, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	// Text
    glDisable( GL_LIGHTING );
	char srctext[25] = "Asterion";
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 10, 0);
	glScalef(0.01, 0.01, 0.01);
	for (int c=0; srctext[c] != 0; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, srctext[c]);
	glPopMatrix();
    glEnable( GL_LIGHTING );
}

/*

void Asterion::move(float xIn, float yIn, float zIn) {
	x = xIn;
	y = yIn;
	z = zIn;
}

void Asterion::rotate(float thetaIn, float phiIn) {
	theta = thetaIn;
	phi = phiIn;
}

*/

void Asterion::draw() {
    glEnable( GL_LIGHTING );
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glScalef(0.4, 0.4, 0.4);
	glRotatef(angleTheta * 180 / M_PI - 90, 0, 1, 0);
	glRotatef(anglePhi * 180 / M_PI - 90, 0, 0, 1);
	buildCar();
	glPopMatrix();
}
