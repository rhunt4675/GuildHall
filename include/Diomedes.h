#ifndef DIOMEDES_H
#define DIOMEDES_H

#include "Hero.h"

class Diomedes : public Hero {
private:
	// car location in CARTESIAN coordinates
	float x, y, z, angle;

	// car WHEEL/ANTENNA rotation in radians
	float wheelRotLeft, wheelRotRight, antennaRot;

	// Draw the car wheel
	void drawWheel();

	// Draw the car body
	void drawBody();

	// Integrate the components of the car
	void buildCar();

public:
	// Default Constructor
	Diomedes();

	// Getters
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	// Setters
	void move(float x, float y, float z);

	// Animate antenna (call this at 50Hz)
	void animate() { antennaRot += 0.07f; }

	// Draw the car
	void draw();

	// Rotate the left car wheels by amt
	void rotateLeftWheel(float amt) { wheelRotLeft += amt; }

	// Rotate the left car wheels by amt
	void rotateRightWheel(float amt) { wheelRotRight += amt; }

	// Adjust the heading of the car by amt
	void adjustHeading(float amt) { angle += amt; }
};

#endif
