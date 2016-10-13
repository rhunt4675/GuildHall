#ifndef LIGHT_H
#define LIGHT_H

#ifdef __APPLE__           // if compiling on Mac OS
    #include <ALUT/alut.h>  // OpenAL Headers
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>

    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else                   // else compiling on Linux OS
 	#include <AL/alut.h>    // OpenAL Headers
    #include <AL/al.h>
    #include <AL/alc.h>

    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include<iostream>

class Light {
    public:
        Light();
        void setDiffuse(float (&color)[4]);
        void setSpecular(float (&color)[4]);
        void setAmbient(float (&color)[4]);
        void setPos(float (&pos)[3]);
        void setDir(float (&dir)[3]);
        void setSpotDir(float (&dir)[3]);
        void setSpotCut(GLfloat angle);
        void setFall(GLfloat fall);
        void setAttenuation(GLenum prop, float value);
        void enable();
        void disable();
    private:
        GLenum id;
        static unsigned short num;

};


#endif
