#include "../include/AntikytheraPet.h"

void AntikytheraPet::loadPath(bezierCurve* curvey){
        path = curvey;
}

void AntikytheraPet::timeEvent(float angle){
    location = path->getNextCordinate();
    ringAngle = angle;
}

void AntikytheraPet::tooglePointVis(){
    path->tooglePointVis();
}

void AntikytheraPet::toogleCurveVis(){
    path->toogleCurveVis();
}

void AntikytheraPet::draw(){
    glPushMatrix();

    //std::cout<<location.getX()<<", "<<location.getY()<<", "<<location.getZ()<<std::endl;
    glTranslatef(location.getX(), location.getY(), location.getZ());
    drawPet();
    glPopMatrix();   
    
    path->draw();
}

void AntikytheraPet::drawPet(){
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(ringAngle,1,0,0);
    drawSphereThingy();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glRotatef(ringAngle,0,0,1);
    glRotatef(ringAngle,0,1,0);
    glScalef(1,1,.4);
    drawRing();
    glPopMatrix();
    
}



AntikytheraPet::AntikytheraPet(bezierCurve* input){
    path = input;
}

void AntikytheraPet::drawSphereThingy(){
    glPushMatrix();
    glColor3f(1-ringColorR, 1-ringColorG, 1-ringColorB);
    glutSolidSphere(.5,20,20);
    glPopMatrix();
}

void AntikytheraPet::drawRing(){
    glPushMatrix();
    glColor3f(ringColorR, ringColorG, ringColorB);
    glutSolidTorus(.2,.8,30,30);
    glPopMatrix();
}

void AntikytheraPet::updateColors(float r, float g, float b){
    ringColorR = r;
    ringColorG = g;
    ringColorB = b;
}
