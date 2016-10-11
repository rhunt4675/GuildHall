#ifndef direction_header
#define direction_header
#include <math.h>
#include"Point.h"
class Direction {
    public:
        float getDirX();
        float getDirY();
        float getDirZ();
        float getVecX();
        float getVecY();
        float getVecZ();
        float getTheta();
        float getPhi();
        float getLength();
        void change_angle(float theta, float phi);
        void rotate(float theta, float phi);
        void change_length(float delta);
        void normalize(float x, float y, float z);
        Direction();
        Direction(float startTheta, float startPhi);
        Direction(Point a, Point b);
        Direction(float deltaX, float deltaY, float deltaZ);
    protected:
        void recomputeOrientation();
        void recomputeAngle();
        float dirX, dirY, dirZ;
        float length;
        float angleTheta, anglePhi;
};
Direction operator*(Direction a, Direction b);
#endif
