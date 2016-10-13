#ifndef MATERIAL_H
#define MATERIAL_H

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


    class Material {
      public:
        void setEmerald();
        void setJade();
        void setObisdian();
        void setPearl();
        void setRuby();
        void setTurquoise();
        void setBrass();
        void setBronze();
        void setChrome();
        void setCopper();
        void setGold();
        void setSilver();
        void setBlackPlastic();
        void setGreenPlastic();
        void setBlackRubber();

        
    };

#endif