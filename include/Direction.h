#ifndef direction_header
#define direction_header
#include <math.h>
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
        void recomputeOrientation();
        void change_angle(float theta, float phi);
        void change_length(float delta);
        Direction(float startTheta, float startPhi, float startLength);
        Direction();
        Direction(float startTheta, float startPhi);
    protected:
        float dirX, dirY, dirZ;
        float length;
        float angleTheta, anglePhi;
};

#endif
