#include "include/context.h"

context::context(){
    for ( int i = 0; i < 128; ++i){
        asciiKeys[i] = false;
    }
    for (int x = 0; x <= xzBound; ++x){
        for (int y = 0; y <= yBound; ++y){
            for (int z = 0; z <= xzBound; ++z){
                if ((x <= xzDead) | (x >= xzBound - xzDead) | (y <= yDead) | (y >= yBound - yDead) | (z <= xzDead) | (z >= xzBound - xzDead) ){ 
                    //This monster checks if the point is in the extra boundry of the grid that denotes out of bounds
                    gameGrid[x][y][z] = true;
                }
                else {
                    gameGrid[x][y][z] = false;
                }
            }
        }
    }
}

bool context::checkBounds(float propsedX, float propsedY, float propsedZ){
    float potentialX = propsedX;
    float potentialY = propsedY;
    float potentialZ = propsedZ;

    int gridCord[3];
    worldToGrid(potentialX,potentialY,potentialZ, gridCord);

    //std::cout<<"Hero Actual Pos ("<<heroX<<" , "<<heroY<<" , "<<heroZ<<")"<<std::endl;
    //std::cout<<"Hero Grid Pos ("<<colX<<" , "<<colY<<" , "<<colZ<<")    "<<gameGrid[colX][colY][colZ]<<std::endl;
    return(!acessGrid(gridCord[0],gridCord[1],gridCord[2]));
}

void context::worldToGrid(float worldX, float worldY, float worldZ, int (&gridCords)[3]){
    worldX += xzOffset;
    worldY += yOffset;
    worldZ += xzOffset;

    worldX /= 2;
    worldY /= 2;
    worldZ /= 2;

    gridCords[0] = int(worldX + .5);
    gridCords[1] = int(worldY + .5);
    gridCords[2] = int(worldZ + .5);
}

void context::removeCollision(float x, float y, float z){
    int gridCord[3];
    worldToGrid(x,y,z, gridCord);
    setGrid(gridCord, false);
}  

void context::worldToGrid(int worldX, int worldY, int worldZ, int (&gridCords)[3]){
    worldX += xzOffset;
    worldY += yOffset;
    worldZ += xzOffset;

    worldX /= 2;
    worldY /= 2;
    worldZ /= 2;

    gridCords[0] = int(worldX + .5);
    gridCords[1] = int(worldY + .5);
    gridCords[2] = int(worldZ + .5);
}

void context::setCollision(float x, float y, float z){
    int gridCord[3];
    worldToGrid(x,y,z, gridCord);
    setGrid(gridCord, true);
}

void context::setCollision(int x, int y, int z){
    int gridCord[3];
    worldToGrid(x,y,z, gridCord);
    setGrid(gridCord, true);
}


void context::bound(int &input, int min, int max){
    if (input < min){
        input = min;
    }
    if (input > max){
        input = max;
    }
}

void context::boundGrid(int &x, int &y, int& z){
    bound(x,0,xzBound);
    bound(y,0,yBound);
    bound(z,0,xzBound);
}   

bool context::acessGrid(int x, int y, int z){
    boundGrid(x,y,z);
    return gameGrid[x][y][z];
}

void context::setGrid(int x, int y, int z, bool state){
    boundGrid(x,y,z);
    gameGrid[x][y][z] = state;
}

void context::setGrid(int (&cord)[3], bool state){
    boundGrid(cord[0],cord[1],cord[2]);
    gameGrid[cord[0]][cord[1]][cord[2]] = state;
}

bool context::getKey(int keyValue){
    bound(keyValue,0,127);
    return asciiKeys[keyValue];
}

void context::setKey(int keyValue, bool state){
    bound(keyValue,0,127);
    asciiKeys[keyValue] = state;
}

// getRand() ///////////////////////////////////////////////////////////////////
//
//  Simple helper function to return a random number between 0.0f and 1.0f.
//
////////////////////////////////////////////////////////////////////////////////
float context::getRand() {
    return rand() / (float)RAND_MAX;
}
