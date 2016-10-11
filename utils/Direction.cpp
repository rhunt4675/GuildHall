#include "../include/Direction.h"

Direction::Direction(float startTheta, float startPhi, float startLength){
    angleTheta = startTheta;
    anglePhi = startPhi;
    length = startLength;
    recomputeOrientation();
}

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
};



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



    double normalize = dirX * dirX + dirY * dirY + dirZ * dirZ;
    normalize = sqrt(normalize);
    dirX /= normalize;
    dirY /= normalize;
    dirZ /= normalize;
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
