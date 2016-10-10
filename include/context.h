#ifndef context_header
#define context_header

#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<iostream>

using namespace std;

class context {
    public:
    bool checkBounds(float propsedX, float propsedY, float propsedZ);
    void setCollision(float x, float y, float z);
    void setCollision(int x, int y, int z);
    bool getKey(int keyVworldContextalue);
    void setKey(int keyValue, bool state);
    float getRand();
    void removeCollision(float x, float y, float z);
    context();
    private:
    
    bool acessGrid(int x, int y, int z);
    void setGrid(int x, int y, int z, bool state);
    void setGrid(int (&cord)[3], bool state);
    void worldToGrid(float worldX, float worldY, float worldZ, int (&gridCords)[3]);
    void worldToGrid(int worldX, int worldY, int worldZ, int (&gridCords)[3]);
    //Keyboard boolean array
    bool asciiKeys[128];
    void bound(int &input, int min, int max);
    void boundGrid(int &x, int &y, int& z);

    //Collision System
    //Divides the world up into 2x2x2 chuncks and keeps track if their is anything in that chunck
    //gride goes from (-60,11,-60) to (60,211,60)
    bool gameGrid[61][123][61];
    const int xzBound = 60;
    const int yBound = 120;
    const int xzOffset = 60;
    const int yOffset = 11;
    const int xzDead = 5;
    const int yDead = 5;
    

};

#endif
