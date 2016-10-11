#include "../include/Camera.h"

void Camera::updateOrientation(float rho, float theta, float phi) {
    x = (rho * sin(theta) * sin(phi));
    y = (-rho * cos(phi));
    z = (-rho * cos(theta) * sin(phi));
    this->rho = rho; this->theta = theta; this->phi = phi;
}

void Camera::updatePosition(float x, float y, float z, float dirX, float dirY, float dirZ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

void Camera::updateCarPosition(float x, float y, float z) {
	carX = x;
	carY = y;
	carZ = z;
}

void Camera::updateUpVector(float x, float y, float z) {
	upX = x;
	upY = y;
	upZ = z;
}

void Camera::doLookAt() {
    glLoadIdentity();

    if (arcBall)
		gluLookAt( x + carX, y + carY, z + carZ,
				carX, carY, carZ,
				upX, upY, upZ);
	else
		gluLookAt( x, y, z,
				x + dirX, y + dirY, z + dirZ,
				upX, upY, upZ);
}

void Camera::enableFreeCam() {
	dirX = -x;
	dirY = -y;
	dirZ = -z;
	
	float magnitude = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
	dirX /= magnitude; dirY /= magnitude; dirZ /= magnitude;

	if (arcBall) {
		x += carX;
		y += carY;
		z += carZ;
	}

	arcBall = false;
}

void Camera::enableArcBallCam() {
	arcBall = true;
}
