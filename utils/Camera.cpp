#include "Camera.h"

void Camera::updateOrientation(float rho, float theta, float phi) {
    x = rho * sin(theta) * sin(phi);
    y = -rho * cos(phi);
    z = -rho * cos(theta) * sin(phi);
    this->rho = rho; this->theta = theta; this->phi = phi;
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
	gluLookAt( carX + x, carY + y, carZ + z,
				carX, carY, carZ,
				upX, upY, upZ);
}