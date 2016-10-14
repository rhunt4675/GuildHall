#include "../include/Light.h"

Light::Light(){
    if (num <= 7) {
        id = GL_LIGHT0 + num;
        //std::cout<<num<<std::endl;
        num++;
        glEnable(id);
    }
    else {
        std::cerr<<"Failed to create light. To many light already exists. Program will still run be will not work as expected. You should really fix this"<<std::endl;
    }
}

unsigned short Light::num = 0;

void Light::setDiffuse(float (&color)[4]){
    glLightfv( id, GL_DIFFUSE, color ); 
}
void Light::setSpecular(float (&color)[4]){
    glLightfv( id, GL_SPECULAR, color ); 
}
void Light::setAmbient(float (&color)[4]){
    glLightfv( id, GL_AMBIENT, color ); 
}
void Light::setPos(float (&in)[3]){
    float pos[4] = {in[0],in[1],in[2],1};
    glLightfv( id, GL_POSITION, pos );
}
void Light::setDir(float (&in)[3]){
    float dir[4] = {in[0],in[1],in[2],0};
    glLightfv( id, GL_POSITION, dir );
}
void Light::setSpotDir(float (&in)[3]){
    float dir[4] = {in[0],in[1],in[2],0};
    glLightfv( id, GL_SPOT_DIRECTION, dir );
}
void Light::setSpotCut(GLfloat angle){
    glLightf( id, GL_SPOT_CUTOFF, angle );
}
void Light::setFall(GLfloat fall){
    glLightf( id, GL_SPOT_EXPONENT, fall );
}
void Light::setAttenuation(GLenum prop, float value){
    glLightf( id, prop, value ); 
}
void Light::enable(){
    glEnable(id);
}
void Light::disable(){
    glDisable(id);
}
