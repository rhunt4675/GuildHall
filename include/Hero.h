#ifndef HERO_H
#define HERO_H

 #ifdef __APPLE__           // if compiling on Mac OS
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else                   // else compiling on Linux OS
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include <cmath>

class Hero {
	public:
		// Draw the hero
		virtual void draw() = 0;

		// Animate the hero at specified frequency
		virtual void animate() = 0;

		// Set the hero position
		virtual void move(float x, float y, float z) = 0;

		// Get the hero position
		virtual float getX() = 0;
		virtual float getY() = 0;
		virtual float getZ() = 0;
};

#endif