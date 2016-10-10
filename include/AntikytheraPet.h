#ifndef pet_header
#define pet_header

#include<iostream>
#include"Point.h"
#include"drawable.h"
#include"bezierCurve.h"

class AntikytheraPet : public drawable {
    public:
       void loadPath(bezierCurve* curvey);
       void timeEvent(float angle);
       void draw();
       void tooglePointVis();
       void toogleCurveVis();
       void updateColors(float r, float g, float b);
       AntikytheraPet(bezierCurve* input);

    private:
        Point location;
        void drawPet();
        void drawSphereThingy();
        void drawRing();
        
         //Sphere and Ring Thingy
        float ringAngle, ringColorR, ringColorG, ringColorB;
        bezierCurve* path;

};

#endif


