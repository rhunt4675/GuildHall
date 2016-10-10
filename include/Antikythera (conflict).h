#include"Point.h"
#include"context.h"
#include"Direction.h"
#include"AntikytheraPet.h"
#include"drawable.h"

class Antikythera : public Point, public Direction, public drawable {
    public:
    void draw();
    void timeEvent(int value);
    Antikythera(float startX, float startY, float startZ, float startTheta, float startPhi, context* point, bezierCurve* petPath );
    Antikythera();
    void tooglePointVis();
    void toogleCurveVis();
    private:
    void drawBody();
    void drawAxel();
    void drawWheel();
    void drawWheelAndAxel();
    void drawDriveTrain(float rotation);
    void drawRocket();
    void drawUnderJets();
    void drawBackJets();
    void updatePos(int direction);
    bool fireRockets(float direction);
    void updateHeroPos(int direction);
    float anglePitch;
    void drawHero();

    AntikytheraPet kitty;
    
    context* worldContext;
    
    //Movement and animation speed paramaters
    const float heroMoveConst = .15;
    const float heroTurnConst = .01;
    const float wheelSpeed = 1;
    const float wheelTurnMult = .7;
    const float wheelStrightMult = 1.5;
    //Hero Posistion and angle
    float leftWheels, rightWheels;
    float ringAngle;
    //Jetpack
    bool airborn;
    float rearFlame;
    float rocketAnimation;
    
        const int key_w = 119;
        const int key_s = 115;
        const int key_a = 97;
        const int key_d = 100;
        const int key_space = 32;
        const int key_r = 114;
        const int key_z = 122 ;
        const int key_x = 120 ;
    
};



