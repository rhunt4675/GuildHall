/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *  Project: GuildHall
 *  File: main.cpp
 *
 *	Author: Ryan Bailey
 *	
 *	Adapated from:
 *	    Dr. Jeffrey Paone - Fall 2015
 *	        lab02
 *
 *
 *  Description:
 *      Contains the GuildHall Code
 *
 */

#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>

#include"include/Antikythera.h"
#include"include/Direction.h"
#include"include/bezierCurveReader.h"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 640;
static size_t windowHeight = 480;
static float aspectRatio;


    //Grid paramaters
    static int gridSize = 50;
    static int gridSpacing = 5;

context WorldContext;
Antikythera* antikythera;
Direction* camcorder;

//Camera Position and angle
//float cameraTheta, cameraPhi, cameraRadius;
//float dirX, dirY, dirZ;


    //Mouse Posistion
    GLint leftMouseButton;              // status of the mouse buttons
    int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
    bool mouseCTRL;


GLuint environmentDL;  //Display list of the enviroment


// drawGrid() //////////////////////////////////////////////////////////////////
//
//  Function to draw a grid in the XZ-Plane using OpenGL 2D Primitives (GL_LINES)
//
////////////////////////////////////////////////////////////////////////////////
void drawGrid() {
    /*
     *	We will get to why we need to do this when we talk about lighting,
     *	but for now whenever we want to draw something with an OpenGL
     *	Primitive - like a line, quad, point - we need to disable lighting
     *	and then reenable it for use with the GLUT 3D Primitives.
     */
    glDisable( GL_LIGHTING );

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    for (int i = -gridSize; i <= gridSize; i+=gridSpacing){
        glVertex3f(-gridSize, 0, i);
        glVertex3f(gridSize, 0, i);
        glVertex3f(i, 0, -gridSize);
        glVertex3f(i, 0, gridSize);
    }
    glEnd();

    glEnable( GL_LIGHTING );
}


void generateEnvironmentDL() {
    environmentDL = glGenLists(1);
    glNewList(environmentDL, GL_COMPILE );
    drawGrid();
    glEndList();
}
/////////////////////////////////////////////////////////////////////////////

// resizeWindow() //////////////////////////////////////////////////////////////
//
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport.
//
////////////////////////////////////////////////////////////////////////////////
void resizeWindow(int w, int h) {
    aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport(0, 0, w, h);

    //update the projection matrix with the new window properties
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100000);
}





// mouseCallback() /////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse clicks. We save the state of the mouse button
//      when this is called so that we can check the status of the mouse
//      buttons inside the motion callback (whether they are up or down).
//
////////////////////////////////////////////////////////////////////////////////
void mouseCallback(int button, int state, int thisX, int thisY) {
        mouseX = thisX;
        mouseY = thisY;
    if(button == GLUT_LEFT_BUTTON){
        leftMouseButton = state;
    }
    //Placed here instead of in mouseMotion becasue mouseMotion could not recive anything from GetModifiers
    mouseCTRL= (glutGetModifiers() == GLUT_ACTIVE_CTRL);
}

// mouseMotion() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse movement. 
//
/////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y) {
    if(leftMouseButton == GLUT_DOWN) {
        if(mouseCTRL) {
            camcorder->change_length(.1 * (mouseY - y));
        }
        else {
            camcorder->change_angle(.005*(x-mouseX), .005*(mouseY-y));
          
        }
    }
    mouseX = x;
    mouseY = y;

}



// initScene() /////////////////////////////////////////////////////////////////
//
//  A basic scene initialization function; should be called once after the
//      OpenGL context has been created. Doesn't need to be called further.
//
////////////////////////////////////////////////////////////////////////////////
void initScene()  {
    glEnable(GL_DEPTH_TEST);

    //******************************************************************
    // this is some code to enable a default light for the scene;
    // feel free to play around with this, but we won't talk about
    // lighting in OpenGL for another couple of weeks yet.
    float lightCol[4] = { 1, 1, 1, 1};
    float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
    float lPosition[4] = { 10, 10, 10, 1 };
    glLightfv( GL_LIGHT0, GL_POSITION,lPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // tell OpenGL not to use the material system; just use whatever we 
    // pass with glColor*()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //******************************************************************

    glShadeModel(GL_FLAT);

    srand( time(NULL) );	// seed our random number generator
    generateEnvironmentDL();
}


// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void)  {
    //clear the render buffer
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glLoadIdentity();
    Point cameraLoc = *antikythera - *camcorder;
    gluLookAt(cameraLoc.getX(), cameraLoc.getY(), cameraLoc.getZ(),      // camera is located at (10,10,10)
            antikythera->getX(),  antikythera->getY(),  antikythera->getZ(),   	// camera is looking at (0,0,0)
            0,  1,  0);     // up vector is (0,1,0) (positive Y)
    
    
    glPushMatrix(); {
        glCallList( environmentDL);
    }; glPopMatrix();

   antikythera->draw();

    //push the back buffer to the screen
    glutSwapBuffers();
}

// myMenu() /////////////////////////////////////////////////////////////////////
//
//  Handles our Menu events
//
////////////////////////////////////////////////////////////////////////////////
void myMenu( int value ) {
    if (value == 0){
        exit(0);
    }
    if (value == 1){
        antikythera->tooglePointVis();
    }
    if (value == 2){
        antikythera->toogleCurveVis();
    }
}

// createMenus() ///////////////////////////////////////////////////////////////
//
//  Handles creating a menu, adding menu entries, and attaching the menu to
//  a mouse button
//
////////////////////////////////////////////////////////////////////////////////
void createMenus() {
    glutCreateMenu(myMenu);
    glutAddMenuEntry("QUIT",0);
    glutAddMenuEntry("Display/Hide Control Cage",1);
    glutAddMenuEntry("Display/Hide Bezier Curve",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// normalKeysDown() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user presses a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysDown(unsigned char key, int x, int y) {
    if(key == 'q' || key == 'Q' || key == 27)   {
        exit(0);
    }
    WorldContext.setKey(key,true);
}

void keyRelease(unsigned char key, int x, int y){
       WorldContext.setKey(key,false); 
}

//Main timmer that controls redraw and passive animation
void mainTimer( int value) {
    antikythera->timeEvent(value);
    glutPostRedisplay();
    glutTimerFunc(6, mainTimer, 0);
}


// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Does not process command line arguments.
//
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Oh The Places You'll Go");
    
    bezierCurveReader reader;
    camcorder = new Direction(-M_PI/3.0f, M_PI/2.8f, 10);
    bezierCurve petPath = reader.simpleRead("petPath.csv");
    antikythera = new Antikythera(10,0,10,M_PI/4,M_PI/2,&WorldContext,&petPath);
    // register callback functions...
    createMenus();
    glutTimerFunc(6, mainTimer, 0);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutKeyboardFunc(normalKeysDown);
    glutKeyboardUpFunc(keyRelease);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resizeWindow);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotion);

    // do some basic OpenGL setup
    initScene();

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
