#include "../include/Material.h"

void Material::setEmerald(){
    GLfloat mat[4];
    mat[0] = .0215;
    mat[1] = .1745;
    mat[2] = .0215;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = .07568;
    mat[1] = .61424;
    mat[2] = .07568;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = .633;
    mat[1] = .727811;
    mat[2] = .633;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, .6 * 128.0);
}
void Material::setJade(){
    GLfloat mat[4];
    mat[0] = 0.135;
    mat[1] = 0.2225;
    mat[2] = 0.1575;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.54;
    mat[1] = 0.89;
    mat[2] = .63;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.316228;
    mat[1] = 0.316228;
    mat[2] = 0.316228;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, .1 * 128.0);
}
void Material::setObisdian(){
    GLfloat mat[4];
    mat[0] = 0.05375;
    mat[1] = 0.05;
    mat[2] = 0.06625;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.18275;
    mat[1] = 0.17;
    mat[2] = 0.22525;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.332741;
    mat[1] = 0.328634;
    mat[2] = 0.346435;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, .3 * 128.0);    
}
void Material::setPearl(){
    GLfloat mat[4];
    mat[0] = 0.25;
    mat[1] = 0.20725;
    mat[2] = 0.20725;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 1;
    mat[1] = .829;
    mat[2] = .829;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.296648;
    mat[1] = 0.296648;
    mat[2] = 0.296648;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, .008 * 128.0);   
}
void Material::setRuby(){
    GLfloat mat[4];
    mat[0] = 0.1745;
    mat[1] = 0.01175;
    mat[2] = 0.01175;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.61424;
    mat[1] = .04136;
    mat[2] = .04136;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.727811;
    mat[1] = 0.626959;
    mat[2] = 0.626959;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, .6 * 128.0);   
}
void Material::setTurquoise(){
    GLfloat mat[4];
    mat[0] = 0.1;
    mat[1] = 0.018725;
    mat[2] = 0.1745;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.396;
    mat[1] = .74151;
    mat[2] = .69102;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.297254;
    mat[1] = 0.30829;
    mat[2] = 0.306678;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, .1 * 128.0);  
}
void Material::setBrass(){
    GLfloat mat[4];
    mat[0] = 0.329412;
    mat[1] = 0.223529;
    mat[2] = 0.027451;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.780392;
    mat[1] = 0.568627;
    mat[2] = 0.113725;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.992157;
    mat[1] = 0.941176;
    mat[2] = 0.807843;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.21794872 * 128.0);
}
void Material::setBronze(){
    GLfloat mat[4];
    mat[0] = 0.2125;
    mat[1] = 0.1275;
    mat[2] = 0.054;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.714;
    mat[1] = 0.4284;
    mat[2] = 0.18144;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.393548;
    mat[1] = 0.271906;
    mat[2] = 0.166721;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.2 * 128.0);
}
void Material::setChrome(){
    GLfloat mat[4];
    mat[0] = 0.25;
    mat[1] = 0.25;
    mat[2] = 0.25;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.4;
    mat[1] = 0.4;
    mat[2] = 0.4;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.774597;
    mat[1] = 0.774597;
    mat[2] = 0.774597;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);
}
void Material::setCopper(){
    GLfloat mat[4];
    mat[0] = 0.19125;
    mat[1] = 0.0735;
    mat[2] = 0.0225;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.7038;
    mat[1] = 0.27048;
    mat[2] = 0.0828;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.256777;
    mat[1] = 0.137622;
    mat[2] = 0.086014;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1 * 128.0);
}
void Material::setGold(){
    GLfloat mat[4];
    mat[0] = 0.24725;
    mat[1] = .1995;
    mat[2] = .0745;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.75164;
    mat[1] = 0.60648;
    mat[2] = 0.22648;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.628281;
    mat[1] = 0.555802;
    mat[2] = 0.366065;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.4 * 128.0);
}
void Material::setSilver(){
    GLfloat mat[4];
    mat[0] = 0.19225;
    mat[1] =  0.19225;
    mat[2] = 0.19225;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.50754;
    mat[1] = 0.50754;
    mat[2] = 0.50754;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.508273;
    mat[1] = 0.508273;
    mat[2] = 0.508273;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.4 * 128.0);
}
void Material::setBlackPlastic(){
    GLfloat mat[4];
    mat[0] = 0;
    mat[1] = 0;
    mat[2] = 0;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.01;
    mat[1] = 0.01;
    mat[2] = 0.01;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = .5;
    mat[1] = .5;
    mat[2] = .5;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128.0);
}
void Material::setGreenPlastic(){
    GLfloat mat[4];
    mat[0] = 0;
    mat[1] = 0;
    mat[2] = 0;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.1;
    mat[1] = 0.35;
    mat[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = .45;
    mat[1] = .55;
    mat[2] = .45;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128.0);
}
void Material::setBlackRubber(){
    GLfloat mat[4];
    mat[0] = 0.02;
    mat[1] = 0.02;
    mat[2] = 0.02;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.01;
    mat[1] = 0.01;
    mat[2] = 0.01;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = .4;
    mat[1] = .4;
    mat[2] = .4;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.078125 * 128.0);
}
