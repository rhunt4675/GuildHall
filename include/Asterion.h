#ifndef ASTERION_H
#define ASTERION_H

#include "Hero.h"

class Asterion : public Hero {
private:
	//float x, y, z, theta, phi;
	int wheelRotation, teapotRotation;

	void drawSpoke();
	void drawWheel();
	void buildCar();

public:
	Asterion() {}
	void draw();
	//void move(float xIn, float yIn, float zIn);
	//void rotate(float thetaIn, float phiIn);
	void animate() { teapotRotation = (teapotRotation + 5) % 360; }

	void rotateLeftWheel(float amount) { wheelRotation = wheelRotation + 15 % 360; }
	void rotateRightWheel(float amount ) { wheelRotation = wheelRotation - 15 % 360; }

        /*
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getTheta() { return theta; }
	float getPhi() { return phi; }
        */

};

#endif
