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
	float dirX, dirY, dirZ;
	bool arcBall;

public:
	// Constructor
	Camera() {
		x = y = z = 0;
		rho = theta = phi = 0;
		upX = upY = upZ = 0;
		carX = carY = carZ = 0;
		dirX = dirY = dirZ = 0;
		arcBall = true;
	};

	// Getters
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getDirX() { return dirX; }
	float getDirY() { return dirY; }
	float getDirZ() { return dirZ; }
	float getRho() { return rho; }
	float getTheta() { return theta; }
	float getPhi() { return phi; }

	// Update camera orientation
	void updateOrientation(float rho, float theta, float phi);
	void updatePosition(float x, float y, float z, float dirX, float dirY, float dirZ);

	// Update the car position
	void updateCarPosition(float x, float y, float z);

	// Update camera up vector
	void updateUpVector(float x, float y, float z);

	// Switch camera modes
	void enableFreeCam();
	void enableArcBallCam();
	bool arcBallEnabled() { return arcBall; }

	// Setup camera look-at direction
	void doLookAt();
};

#endif
