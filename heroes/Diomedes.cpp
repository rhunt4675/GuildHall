#include "../include/Diomedes.h"

// CTOR /////////////////////////////////////////////////////////////////
//
// Constructs car object given start location, angle, path
//
/////////////////////////////////////////////////////////////////////////
Diomedes::Diomedes() {
	x = y = z = theta = phi = 0;
}

// draw() /////////////////////////////////////////////////////////////////
//
// Publicly-accessible wrapper for buildCar()
//
///////////////////////////////////////////////////////////////////////////
void Diomedes::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(theta * 180 / M_PI - 90, 0, 1, 0);
    glRotatef(phi * 180 / M_PI - 90, 0 , 0 , 1);
    buildCar();
    glPopMatrix();
}

// move() /////////////////////////////////////////////////////////////////
//
// Move the car to the specified location
//
///////////////////////////////////////////////////////////////////////////
void Diomedes::move(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// rotate() /////////////////////////////////////////////////////////////////
//
// Rotate the car by the specified amount
//
///////////////////////////////////////////////////////////////////////////
void Diomedes::rotate(float theta, float phi) {
    this->theta = theta;
    this->phi = phi;
}

// drawWheel() /////////////////////////////////////////////////////////////////
//
// Renders a car wheel, centered at the geometric center of the wheel
//
////////////////////////////////////////////////////////////////////////////////
void Diomedes::drawWheel() {
	// Draw the Tire
	glColor3ub(50, 50, 50);
	glutSolidTorus(0.5, 1, 30, 50);

	// Draw the Spokes
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glScalef(0.1, 1, 0.2);
	glutSolidCube(2);
	glScalef(10, 0.1, 1);
	glutSolidCube(2);
	glPopMatrix();

	// Draw the Hub Caps
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslatef(0, 0, 0.25);
	glutSolidCone(0.1, 0, 20, 20);
	glTranslatef(0, 0, -0.5);
	glutSolidCone(0.1, 0, 20, 20);
	glPopMatrix();
}

// drawBody() /////////////////////////////////////////////////////////////////
//
// Renders a car body, centered at the geometric center of the wheel
//
////////////////////////////////////////////////////////////////////////////////
void Diomedes::drawBody() {
	// Draw Body
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScalef(6, 1, 3);
	glutSolidCube(1);
	glPopMatrix();

	// Draw Antenna
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslatef(-2.5, 2, 0);
	glRotatef(antennaRot * 180 / M_PI, 0, 1, 0);
	glutSolidTorus(0.1, 0.5, 20, 20);
	glPopMatrix();

	// Draw Antenna Mount
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslatef(-2.5, 1, 0);
	glScalef(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	// Draw Arrow Body
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslatef(0, 0.55f, 0);
	glScalef(3.5, 0, 1);
	glutSolidCube(1);
	glPopMatrix();

	// Draw Arrow Point
    glDisable( GL_LIGHTING );
    glBegin(GL_TRIANGLES); {
    	glVertex3f(1, 0.55f, -1);
    	glVertex3f(1, 0.55f, 1);
    	glVertex3f(2.5, 0.55f, 0);
    }
    glEnd();
    glEnable( GL_LIGHTING );
}

// buildCar() ///////////////////////////////////////////////////////////////////
//
// Renders the hero's vehicle, centered at the geometric center of the car
//
////////////////////////////////////////////////////////////////////////////////
void Diomedes::buildCar() {
    // Front Left Wheel
	glPushMatrix();
	glTranslatef(-2.5, 1.5, -2);
	glRotatef(wheelRotLeft * 180 / M_PI, 0, 0, 1);
    drawWheel();
    glPopMatrix();

    // Front Right Wheel
	glPushMatrix();
	glTranslatef(-2.5, 1.5, 2);
	glRotatef(wheelRotRight * 180 / M_PI, 0, 0, 1);
    drawWheel();
    glPopMatrix();

    // Back Left Wheel
	glPushMatrix();
	glTranslatef(2.5, 1.5, -2);
	glRotatef(wheelRotLeft * 180 / M_PI, 0, 0, 1);
    drawWheel();
    glPopMatrix();

    // Back Right Wheel
	glPushMatrix();
	glTranslatef(2.5, 1.5, 2);
	glRotatef(wheelRotRight * 180 / M_PI, 0, 0, 1);
    drawWheel();
    glPopMatrix();

    // Car Body
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    drawBody();
    glPopMatrix();

	// Text
    glDisable( GL_LIGHTING );
	char srctext[25] = "Diomedes";
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 5, 0);
	glScalef(0.005, 0.005, 0.005);
	for (int c=0; srctext[c] != 0; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, srctext[c]);
	glPopMatrix();
    glEnable( GL_LIGHTING );
}