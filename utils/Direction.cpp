#include "../include/Direction.h"


Direction::Direction(float startTheta, float startPhi){
    angleTheta = startTheta;
    anglePhi = startPhi;
    length = 1;
    recomputeOrientation();
}

Direction::Direction(){
    angleTheta = 0;
    anglePhi = 0;
    length = 1;
    recomputeOrientation();
}

Direction::Direction(Point a, Point b){
    dirX = a.getX() - b.getX();
    dirY = a.getY() - b.getY();
    dirZ = a.getZ() - b.getZ();
    
    recomputeAngle();
}

Direction::Direction(float deltaX, float deltaY, float deltaZ){
    dirX = deltaX;
    dirY = deltaY;
    dirZ = deltaZ;
    
    recomputeAngle();
}


void Direction::recomputeAngle(){
    length = dirX * dirX + dirY * dirY + dirZ * dirZ;
    length = sqrt(length);
    dirX /= length;
    dirY /= length;
    dirZ /= length;

    //TODO: Figure out and implement this caculation
   //angleTheta = acos(dirZ/length);
   //anglePhi = atan2(dirY,dirX);

}

Direction operator* (Direction a, Direction b){
    return Direction(a.getDirY() * b.getDirZ() - a.getDirZ() * b.getDirY(), a.getDirZ() * b.getDirX() - a.getDirX() * b.getDirZ(), a.getDirX() * b.getDirY() - a.getDirY() * b.getDirX());    
}

void Direction::rotate(float theta, float phi){
    angleTheta = theta;
    anglePhi = phi;
    recomputeOrientation();
}

float Direction::getDirX(){
    return dirX;
}

float Direction::getDirY(){
    return dirY;
}

float Direction::getDirZ(){
    return dirZ;
}

float Direction::getLength(){
    return length;
}

float Direction::getVecX(){
    return dirX * length;
}

float Direction::getVecY(){
    return dirY * length;
}

float Direction::getVecZ(){
    return dirZ * length;
}



void Direction::recomputeOrientation() {
    dirX = sin(angleTheta)*sin(anglePhi);
    dirY = -cos(anglePhi);
    dirZ = cos(angleTheta)*sin(anglePhi);



    double size = dirX * dirX + dirY * dirY + dirZ * dirZ;
    size = sqrt(size);
    dirX /= size;
    dirY /= size;
    dirZ /= size;
}

void Direction::change_angle(float theta, float phi){
    angleTheta += theta;       
    anglePhi += phi;
    if(anglePhi < 0){
        anglePhi = 0;
    }
    if (anglePhi > M_PI){
        anglePhi = M_PI;
    }
    recomputeOrientation();
}

float Direction::getTheta(){
    return angleTheta;
}

float Direction::getPhi(){
    return anglePhi;
}

void Direction::change_length(float delta){
    length += delta;
    if(length < 0){
        length = 0;
    }
}

void Direction::normalize(float x, float y, float z){
    dirX = x;
    dirY = y;
    dirZ = z;
    recomputeAngle();
}
