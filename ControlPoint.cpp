#include "include/ControlPoint.h"

ControlPoint operator*( ControlPoint p, float f ) {
    return ControlPoint( p.getX() * f, p.getY() * f, p.getZ() * f );
}



void ControlPoint::click_toggle(bool click){
    selected = click;
}


void ControlPoint::draw(){
    glPushMatrix();
    glTranslatef(posX,posY,posZ);
    if(!selected){
        glColor3f(colorR,colorG,colorB);
    }
    else {
        glColor3ub(altR,altG,altB);
    }
    glutSolidSphere(.25,20,20);
    glPopMatrix();
}

ControlPoint::ControlPoint(float thisX, float thisY, float thisZ) : Point(thisX, thisY, thisZ), drawable(){
    selected = false;
    colorR = 0;
    colorG = 1;
    colorB = 0;
}

ControlPoint::ControlPoint() : Point(), drawable(){

}

