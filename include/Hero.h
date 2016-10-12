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
#include "Point.h"
#include "Direction.h"

class Hero: public Point, public Direction{
	public:
		// Draw the hero
		virtual void draw() = 0;

		// Animate the hero at specified frequency
		virtual void animate() = 0;

		// Set the hero position

		// Get the hero position
			
                // Rotate the wheels (if applicable)
		virtual void rotateLeftWheel(float amt) = 0;
		virtual void rotateRightWheel(float amt) = 0;

		// Set the car pitch
		virtual void setPitch(float amt) = 0;
};

#endif
