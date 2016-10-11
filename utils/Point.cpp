#include "../include/Point.h"

Point operator*( Point p, float f ){
        return Point( p.getX() * f, p.getY() * f, p.getZ() * f );
}

Point operator*(float f, Point p ) {
    return Point( p.getX() * f, p.getY() * f, p.getZ() * f );
}
Point operator+( Point a, Point b ) {
    return Point( a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Point operator-( Point p, Direction d){
    return Point( p.getX() - d.getVecX(), p.getY() - d.getVecY(), p.getZ() - d.getVecZ() );
}

Point operator+( Point p, Direction d){
    return Point( p.getX() + d.getVecX(), p.getY() + d.getVecY(), p.getZ() + d.getVecZ() );
}

Point operator+(Direction d, Point p){
    return Point( p.getX() + d.getVecX(), p.getY() + d.getVecY(), p.getZ() + d.getVecZ() );
}


void Point::move(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}

float Point::getX(){
    return posX;
}

float Point::getY(){
    return posY;
}

float Point::getZ(){
    return posZ;
}

float* Point::getPos(){
    updateCords();
    return cords;
}

Point::Point(){
    posX = 0;
    posY = 0;
    posZ = 0;
}

Point::Point(float startX, float startY, float startZ){
    posX = startX;
    posY = startY;
    posZ = startZ;
}

void Point::change_pos(float x, float y, float z){
        posX += x;       
        posY += y;
        posZ += z;
}

void Point::updateCords(){
    cords[0] = posX;
    cords[1] = posY;
    cords[2] = posZ;
}
