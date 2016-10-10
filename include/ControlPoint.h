#ifndef point_header
#define point_header

#ifdef __APPLE__            // if compiling on Mac OS
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else                   // else compiling on Linux OS
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include"drawable.h"
#include"Point.h"

class ControlPoint : public Point , public drawable{
    public:
    ControlPoint();
    ControlPoint(float thisX, float thisY, float thisZ);
    void draw();
    void click_toggle(bool click);
    private:
    bool selected;
    float colorR,colorG,colorB;
    float altR,altG,altB;
};

#endif
