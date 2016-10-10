#ifndef CAMERA_H
#define CAMERA_H

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <cmath>

class Camera {
private:
	float x, y, z;
	float rho, theta, phi;
	float upX, upY, upZ;
	float carX, carY, carZ;

public:
	// Constructor
	Camera() {
		x = y = z = 0;
		rho = theta = phi = 0;
		upX = upY = upZ = 0;
		carX = carY = carZ = 0;
	};

	// Getters
	float getRho() { return rho; }
	float getTheta() { return theta; }
	float getPhi() { return phi; }

	// Update camera orientation
	void updateOrientation(float rho, float theta, float phi);

	// Update the car position
	void updateCarPosition(float x, float y, float z);

	// Update camera up vector
	void updateUpVector(float x, float y, float z);

	// Setup camera look-at direction
	void doLookAt();
};

#endif
