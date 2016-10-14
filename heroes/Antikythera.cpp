#include "../include/Antikythera.h"


/*Antikythera::Antikythera(float startX, float startY, float startZ, float startTheta, float startPhi, context* point, bezierCurve* petPath) : kitty(petPath) {
    worldContext = point;
    airborn = false;
    anglePitch = 0;
    kitty.updateColors(worldContext->getRand(),worldContext->getRand(),worldContext->getRand());
    worldContext->removeCollision(startX,startY,startZ);
    leftWheels = 0;
    rightWheels = 0;
}*/

Antikythera::Antikythera() {
    headLamp.enable();
    GLfloat cut = 12;
    GLfloat fall = 100;
    float diffuseCol[4] = { .5, .5, .5, 1.0 };
    float ambientCol[4] = { 0.1, 0.1, 0.1, 1.0 };
    headLamp.setDiffuse(diffuseCol);
    headLamp.setAmbient(ambientCol);
    headLamp.setSpecular(ambientCol);
    //headLamp.setSpotCut(cut);
    //headLamp.setFall(fall);
    flashLightAngle = 0;
    flashLightUp = true;
}

//Draws the main body
void Antikythera::drawBody(){
    glPushMatrix();
    cloth.setTurquoise();
    glScalef(8,1,2);
    glutSolidCube(1);
    glPopMatrix();

}

void Antikythera::drawAxel(){
    glPushMatrix();
    cloth.setJade();
    glutSolidCone(.7,3,20,20);
    glPopMatrix();
}

void Antikythera::drawWheel(){
    glPushMatrix();
    cloth.setBlackRubber();
    glutSolidTorus(.4, .7, 20, 20);
    glPopMatrix();
}

//Draws a wheel with an axel attached. Takes in the roatation of the wheel in degress
void Antikythera::drawWheelAndAxel(){
    glPushMatrix();
    glTranslatef(0,0,1.7);
    drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    drawAxel();
    glPopMatrix();
}

void Antikythera::drawDriveTrain(float rotation){
    glPushMatrix();
    glTranslatef(2,0,0);
    glRotatef((rotation),0,0,1);
    drawWheelAndAxel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef((rotation),0,0,1);
    drawWheelAndAxel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,0,0);
    glRotatef((rotation),0,0,1);
    drawWheelAndAxel();
    glPopMatrix();

}

//Draws a Rocket
void Antikythera::drawRocket(){
    cloth.setRuby();
    glPushMatrix();
    glutSolidCone(.5,2,20,20);
    glPopMatrix();
}
//draws the rockets for the under Jet
void Antikythera::drawUnderJets(){
    float vis = (rocketAnimation > 0) ? 1 : 0;

    glPushMatrix();
    glTranslatef(1.5,1.5,0);
    glScalef(vis,vis,rocketAnimation);
    drawRocket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-1.5,0);
    glScalef(vis,vis,rocketAnimation);
    drawRocket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,1.5,0);
    glScalef(vis,vis,rocketAnimation);
    drawRocket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,-1.5, 0);
    glScalef(vis,vis,rocketAnimation);
    drawRocket();
    glPopMatrix();
}

//Draws the back jets
void Antikythera::drawBackJets(){
    float vis = (rearFlame > 0) ? 1 : 0;
    glPushMatrix();
    glTranslatef(-1,0,0);
    glScalef(vis,vis,rearFlame);
    drawRocket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,0);
    glScalef(vis,vis,rearFlame);
    drawRocket();
    glPopMatrix();
}

void Antikythera::drawHero(){
    glEnable( GL_LIGHTING );
    glPushMatrix();
    glTranslatef(2.3,2.3,0);
    glRotatef(-90,0,1,0);
    glRotatef(flashLightAngle,0,1,0);
    glPushMatrix();
        glTranslatef(3,5,0);
        //float pos[3] = {3,3,3};
        //headLamp.setPos(pos);
        float dir[3] = {0,0,0};
        headLamp.setDir(dir);
        //headLamp.enable();
    glPopMatrix();
    cloth.setChrome();
    glutSolidCone(1,3,20,20);
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(-2,1,0);
    drawBody();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.7,0);
    drawDriveTrain(-rightWheels);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.7,0);
    glRotatef(180,1,0,0);
    drawDriveTrain(leftWheels);
    glPopMatrix();

    /*
    glPushMatrix();
    glRotatef(90,1,0,0);
    drawUnderJets();
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(-6,1,0);
    glRotatef(-90,0,1,0);
    drawBackJets();
    glPopMatrix();
*/
    // Text
    glDisable( GL_LIGHTING );
    char srctext[25] = "Antikythera";
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, 4, 0);
    glScalef(0.005, 0.005, 0.005);
    for (int c=0; srctext[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, srctext[c]);
    glPopMatrix();
    glEnable( GL_LIGHTING );


}

//Draws the hero character/vehicle
void Antikythera::draw(){
    glPushMatrix(); 
    glTranslatef(posX, posY, posZ);
    glRotatef(angleTheta * 180 / M_PI - 90, 0 , 1, 0);
    glRotatef(anglePhi * 180 / M_PI, 0 , 0 , 1);
    //glRotatef(pitch, 1 , 0 ,0);
    drawHero();
    //kitty.draw();
    glPopMatrix();
}

void Antikythera::animate(){
    flashLightAngle += flashLightUp ? 2 : -2;
    if (flashLightAngle >= 60){
        flashLightUp = false;
    }
    if (flashLightAngle <= -60){
        flashLightUp = true;
    }
}


/*
// Moves the hero/vehicle
void Antikythera::move(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z; 
}

// Rotates the hero/vehicle
void Antikythera::rotate(float theta, float phi) {
    this->theta = theta;
    this->phi = phi;
}

*/
/*//Handles the movement caculations for the hero. Converting the hero's theta into a change in the hero's position
void Antikythera::updateHeroPos(int direction){

    recomputeOrientation();

    //std::cout<<"Hero Angle ("<<heroTheta * 180 / M_PI <<" , "<<heroPhi * 180 / M_PI<<" , "<<heroPitch<<")"<<std::endl;

    //Scale movement by the movement speed and revese direction if heading backwards
    float h_dirX = direction * heroMoveConst * dirX;
    float h_dirY = direction * heroMoveConst * dirY;
    float h_dirZ = direction * heroMoveConst * dirZ;
    //Checks if the movement would colide with anythying
    if (worldContext->checkBounds(h_dirX + posX, h_dirY + posY, h_dirZ + posZ)){
        change_pos(h_dirX,h_dirY,h_dirZ);
    }   


}*/

/*bool Antikythera::fireRockets(float direction){
    if(worldContext->checkBounds(posX,posY+direction,posZ)){
        change_pos(0,direction,0);
        return true;
    }
    else {
        return false;
    }
}


void Antikythera::timeEvent(int value){
    airborn = fireRockets(-.3);
    if(worldContext->getKey(key_space)){
        rocketAnimation = 4;
        airborn = fireRockets(1);
    }
    if (!airborn){
        anglePhi = M_PI / 2;
        anglePitch = 0;
    }
    if(worldContext->getKey(key_a)){
        if(!airborn){
            leftWheels -= wheelSpeed * wheelTurnMult;
            rightWheels += wheelSpeed * wheelTurnMult;
        }
        angleTheta += heroTurnConst;
    }
    if(worldContext->getKey(key_d)){
        if(!airborn){
            leftWheels += wheelSpeed * wheelTurnMult;
            rightWheels -= wheelSpeed * wheelTurnMult;
        }
        angleTheta -= heroTurnConst;
    }
    if (worldContext->getKey(key_z) && airborn){
        anglePitch += 1;
    }
    if (worldContext->getKey(key_x) && airborn){
        anglePitch -= 1;
    }
    if(worldContext->getKey(key_w)){
        if (!airborn){
            updateHeroPos(1);
            leftWheels += wheelSpeed * wheelStrightMult; 
            rightWheels += wheelSpeed * wheelStrightMult;
        } 
        else {
            anglePhi -= .05;
            updateHeroPos(.3);
        }
    }
    if(worldContext->getKey(key_s)){
        if (!airborn){
            updateHeroPos(-1);
            leftWheels -= wheelSpeed * wheelStrightMult;
            rightWheels -= wheelSpeed * wheelStrightMult;
        }
        else {
            anglePhi += .05;
            updateHeroPos(-.3);
        }
    }
    if (worldContext->getKey(key_r)){
        updateHeroPos(12);
        rearFlame = 4;
    }
    if (rocketAnimation > 0){
        rocketAnimation -= .1;
    }
    if (rearFlame > 0){
        rearFlame -=.1;
    }
    ringAngle += .5;
    if (ringAngle == 360){
        ringAngle = 0;
        kitty.updateColors(worldContext->getRand(),worldContext->getRand(),worldContext->getRand());
    }
    kitty.timeEvent(ringAngle);   
}*/

/*void Antikythera::togglePointVisibility(){
    kitty.tooglePointVis();
}
void Antikythera::toggleCurveVisibility(){
    kitty.toogleCurveVis();
}*/
