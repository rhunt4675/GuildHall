#include "../include/Camera.h"

void Camera::updateOrientation(float rho, float theta, float phi) {
    posX = (rho * sin(theta) * sin(phi));
    posY = (-rho * cos(phi));
    posZ = (-rho * cos(theta) * sin(phi));
    this->rho = rho; this->angleTheta = theta; this->anglePhi = phi;
}

void Camera::updatePosition(float x, float y, float z, float dirX, float dirY, float dirZ) {
	this->posX = x;
	this->posY = y;
	this->posZ = z;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

void Camera::updateCarPosition(float x, float y, float z) {
	car.move(x,y,z);
}

void Camera::updateCarPosition(Point pos) {
        car = pos;
}
void Camera::updateUpVector(float x, float y, float z) {
	upVec.normalize(x,y,z);
}
void Camera::updateUpVector(Direction up) {
    upVec = up;
}

void Camera::doLookAt() {
    glLoadIdentity();

    if (arcBall)
		gluLookAt( posX + car.getX(), posY + car.getY(), posZ + car.getZ(),
				car.getX(), car.getY(), car.getZ(),
				upVec.getDirX(), upVec.getDirY(), upVec.getDirZ());
	else
		gluLookAt( posX, posY, posZ,
				posX + dirX, posY + dirY, posZ + dirZ,
				upVec.getDirX(), upVec.getDirY(), upVec.getDirZ());
}

void Camera::enableFreeCam() {
    normalize(-posX,-posY,-posZ);
    /*
        dirX = -posX;
	dirY = -posY;
	dirZ = -posZ;
	
	float magnitude = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
	dirX /= magnitude; dirY /= magnitude; dirZ /= magnitude;

        */
	if (arcBall) {
		posX += car.getX();
		posY += car.getY();
		posZ += car.getZ();
	}

	arcBall = false;
}

void Camera::enableArcBallCam() {
	arcBall = true;
}
