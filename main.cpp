/*
 *  CSCI 441, Computer Graphics, Fall 2016
 *
 *  Project: A04
 *  File: .cpp
 *
 *	Author: Ryan Hunt - Fall 2016
 *
 *  Description:
 *      Contains the base code for the flying hero sprite.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <sys/time.h>

 #ifdef __APPLE__           // if compiling on Mac OS
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else                   // else compiling on Linux OS
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "include/Antikythera.h"
#include "include/Diomedes.h"
#include "include/Asterion.h"
#include "include/Direction.h"
#include "include/Camera.h"
#include "include/bezierCurve.h"
#include "include/InputReader.h"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 640;
static size_t windowHeight = 480;
static float aspectRatio;

GLint leftMouseButton;                      // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
int keys[26] = {0};                         // key state array

GLuint environmentDL;                       // display list for the 'city'
static int cityLength = 50;                 // city boundaries

Camera camera, fpcamera;					// world camera
Hero *antikythera, *diomedes, *asterion;    // hero vehicles
Hero *wanderer, *camerafollower, *fol1, *fol2;
bezierCurve heroPath1, heroPath2;
Point prevPoint1, prevPoint2;
vector<Point> surfacePoints;
//Sprite sprite;								// hero's sprite

//std::vector<Point> points;					// Bezier control points
//bool displayBezierCurve = true;				// Toggle Bezier curve visibility
//bool displayControlCage = true;				// Toggle control cage visibility
bool displayFPCamera = false;				// Toggle first person camera
int frames = 1;
long int start_millis = 0;

// getRand() ///////////////////////////////////////////////////////////////////
//
//  Simple helper function to return a random number between 0.0f and 1.0f.
//
////////////////////////////////////////////////////////////////////////////////
float getRand() {
   	return rand() / (float)RAND_MAX;
}

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

	glColor3ub(50, 50, 50);

	int res = bezierCurve::getResolution();
	for (unsigned int i = 0; i < surfacePoints.size() / res; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j < res / 2; j++) {
			glVertex3fv(surfacePoints[i * res + 2 * j].getPos());
			glVertex3fv(surfacePoints[i * res + 2 * j + res].getPos());
		}
		glEnd();
	}

    /** TODO #3: DRAW A GRID IN THE XZ-PLANE USING GL_LINES **/
//    glBegin(GL_LINES); {
//    	glColor3ub(50, 50, 50);
//        for (int i = -cityLength; i <= cityLength; i++) {
//            glVertex3f(i, 0, -50);
//            glVertex3f(i, 0, 50);
//            glVertex3f(-50, 0, i);
//            glVertex3f(50, 0, i);
//        }
//    } glEnd();
    /*
     *	As noted above, we are done drawing with OpenGL Primitives, so we
     *	must turn lighting back on.
     */
    glEnable( GL_LIGHTING );
}

// drawTrees() //////////////////////////////////////////////////////////////////
//
//  Function to draw buildings on top of the XZ-Plane using GLUT privitives
//
////////////////////////////////////////////////////////////////////////////////
void drawTrees() {
    for (int i = -cityLength; i < cityLength; i++) {
        for (int j = -cityLength; j < cityLength; j++) {
            if (getRand() < 0.001f) {
                int height = getRand() * 5 + 10;

                glPushMatrix();
                glColor3ub(87, 35, 7);
                glTranslatef(i, height / 2.0, j);
                glScalef(1, height, 1);
                glutSolidCube(1);
                glPopMatrix();

                glPushMatrix();
                glColor3ub(53, 98, 68);
                glTranslatef(i, height, j);
                glRotatef(-90, 1, 0, 0);
                glutSolidCone(3, 5, 20, 20);
                glTranslatef(0, 0, -3);
                glutSolidCone(3, 5, 20, 20);
				glTranslatef(0, 0, -3);
                glutSolidCone(3, 5, 20, 20);
                glPopMatrix();
            }
        }
    }
}

// generateEnvironmentDLOA() /////////////////////////////////////////////////////
//
//  This function creates a display list with the code to draw a simple 
//      environment for the user to navigate through.
//
//  And yes, it uses a global variable for the display list.
//  I know, I know! Kids: don't try this at home. There's something to be said
//      for object-oriented programming after all.
//
////////////////////////////////////////////////////////////////////////////////
void generateEnvironmentDL() {
    // TODO #1 Create a Display List & Call our Drawing Functions
    environmentDL = glGenLists(1);

    glNewList(environmentDL, GL_COMPILE);
    
    drawGrid();
    drawTrees();
    glEndList();
}

// resizeWindow() //////////////////////////////////////////////////////////////
//
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport.
//
////////////////////////////////////////////////////////////////////////////////
void resizeWindow(int w, int h) {
    aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;
}

// mouseCallback() /////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse clicks. We save the state of the mouse button
//      when this is called so that we can check the status of the mouse
//      buttons inside the motion callback (whether they are up or down).
//
////////////////////////////////////////////////////////////////////////////////
void mouseCallback(int button, int state, int thisX, int thisY) {
	if (camera.arcBallEnabled()) {
		// Camera state
		float cameraRho = camera.getLength();
		float cameraTheta = camera.getTheta();
		float cameraPhi = camera.getPhi();

	    // update the left mouse button states, if applicable
	    if (button == GLUT_LEFT_BUTTON) {
	        leftMouseButton = state;

	        if (state == GLUT_DOWN) {
	            mouseX = thisX;
	            mouseY = thisY;
	        }
	    } else if (button == 3) { // Wheel
	        if (state == GLUT_UP) return;
	        cameraRho -= 2;
			cameraRho = (cameraRho < 5 ? 5 : cameraRho);
	    } else if (button == 4) { // Wheel
	        if (state == GLUT_UP) return;
	        cameraRho += 2;
			cameraRho = (cameraRho > 100 ? 100 : cameraRho);
	    }

	    camera.updateOrientation(cameraRho, cameraTheta, cameraPhi);
	    glutPostRedisplay();        // redraw our scene from our new camera POV
	} else {
	    if(button == GLUT_LEFT_BUTTON) {
	        leftMouseButton = state;

	        if (state == GLUT_DOWN) {
	            mouseX = thisX;
	            mouseY = thisY;
	        }
	    }
	}
}

// mouseMotion() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse movement. We update cameraPhi, cameraTheta, and/or
//      cameraRadius based on how much the user has moved the mouse in the
//      X or Y directions (in screen space) and whether they have held down
//      the left or right mouse buttons. If the user hasn't held down any
//      buttons, the function just updates the last seen mouse X and Y coords.
//
////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y) {
	// Camera state
	float cameraRho = camera.getLength();
	float cameraTheta = camera.getTheta();
	float cameraPhi = camera.getPhi();

	if (leftMouseButton == GLUT_DOWN && camera.arcBallEnabled()) {
        if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
            cameraRho -= (y - mouseY) * 0.1;
            cameraRho = (cameraRho < 5 ? 5 : (cameraRho > 100 ? 100 : cameraRho));
        } else {
            cameraTheta += (x - mouseX) * 0.005;
            cameraPhi += (y - mouseY) * 0.005;
            cameraPhi = (cameraPhi > M_PI ? M_PI - 0.001 : (cameraPhi < M_PI / 2 ? M_PI / 2 : cameraPhi));
        }
        
        camera.updateOrientation(cameraRho, cameraTheta, cameraPhi);
        glutPostRedisplay();	    // redraw our scene from our new camera POV

    } else if (leftMouseButton == GLUT_DOWN && !camera.arcBallEnabled()) {
        float deltaTheta = -(x - mouseX) * 0.005;
        float deltaPhi = -(y - mouseY) * 0.005;

        camera.change_angle(deltaTheta, deltaPhi);
        glutPostRedisplay();
        // Check Phi Bounds
        //if (cameraPhi < 0) cameraPhi = 0.001;
        //else if (cameraPhi > M_PI) cameraPhi = M_PI - 0.001;
    }

    mouseX = x;
    mouseY = y;
}

// normalKeysDown() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user presses a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysDown(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    } else if (key >= 'a' && key <= 'z') {
        keys[key - 'a'] = 1;
    }
}

// normalKeysUp() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user releases a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysUp(unsigned char key, int x, int y) {
    if (key >= 'a' && key <= 'z')
        keys[key - 'a'] = 0;
}

// initScene() /////////////////////////////////////////////////////////////////
//
//  A basic scene initialization function; should be called once after the
//      OpenGL context has been created. Doesn't need to be called further.
//
////////////////////////////////////////////////////////////////////////////////
void initScene()  {
    glEnable(GL_DEPTH_TEST);

    //******************************************************************//
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
    //******************************************************************//

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
void renderScene()  {
    // clear the render buffer
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update viewport perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,aspectRatio,0.1,100000);

    // update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glViewport(0, 0, windowWidth, windowHeight);
    camera.doLookAt();

    // Display the Environment
    glCallList(environmentDL);

	// Display the Cars
	diomedes->draw();
	antikythera->draw();
	asterion->draw();

    // Optionally display 1st Person Camera
    if (displayFPCamera) {

	    // First-Person Cam
	    glClear(GL_DEPTH_BUFFER_BIT);
	    glViewport(2*windowWidth/3, 0, windowWidth/3, windowHeight/3);
	    fpcamera.doLookAt();
	    
	    // Display the Environment
	    glCallList(environmentDL);

	    // Display the Cars
	    diomedes->draw();
            glPushMatrix();
            glTranslatef(diomedes->getX(), diomedes->getY(), diomedes->getZ());
	    antikythera->draw();
	    asterion->draw();
            glPopMatrix();
	}

	// Draw the Real-Time FPS in the bottom left
	{
		// Calculate FPS
	    struct timeval tp;
		gettimeofday(&tp, NULL);
		long int millis = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	    char *stat = new char[100];
	    sprintf(stat, "FPS: %3.2f", 1000.f * (float) frames / (millis - start_millis));

		// Draw frames per second
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
    	glLoadIdentity();
    	glOrtho( 0, 200, 0, 200, -1, 1);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable( GL_CULL_FACE );
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, windowWidth, windowHeight);

	    glDisable( GL_LIGHTING );
		glPushMatrix();
		glColor3f(1, 1, 1);
		glScalef(0.05, 0.05, 0.05);
		for (int c=0; stat[c] != 0; ++c)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, stat[c]);
		glPopMatrix();
		glEnable( GL_LIGHTING ); 
	    delete stat;
	}

    // push the back buffer to the screen
    glutSwapBuffers();

    // update the counter
    frames++;
}

// myTimer() ////////////////////////////////////////////////////////////
//
//  GLUT timer callback; runs at 50 Hz.
//
////////////////////////////////////////////////////////////////////////////////
void myTimer (int value) {

	// calculate surface normal at current location
	Point point0 = surfacePoints[(int((wanderer->getX() + 50) / 100 * bezierCurve::getResolution()) * bezierCurve::getResolution() + int((wanderer->getZ() + 50) / 100 * bezierCurve::getResolution()))];
	Point point1 = surfacePoints[(int((wanderer->getX() + 50 + sin(wanderer->getTheta())) / 100 * bezierCurve::getResolution()) * bezierCurve::getResolution() + int((wanderer->getZ() + 50 + cos(wanderer->getTheta())) / 100 * bezierCurve::getResolution()))];
	Point point2 = surfacePoints[(int((wanderer->getX() + 50 + sin(wanderer->getTheta() - M_PI / 2)) / 100 * bezierCurve::getResolution()) * bezierCurve::getResolution() + int((wanderer->getZ() + 50 + cos(wanderer->getTheta() - M_PI / 4) + 1) / 100 * bezierCurve::getResolution()))];

	Direction a(point1, point0);
	Direction b(point2,point0);

    Direction cross = a * b;

	float newPhi = acos(cross.getDirY()) - M_PI / 2;
	if (point0.getY() < point1.getY()) newPhi = M_PI - newPhi;
	if (newPhi < 0) newPhi *= -1;
	if (newPhi > M_PI) newPhi -= M_PI;
	
	if (!(newPhi != newPhi))
		wanderer->rotate(wanderer->getTheta(), newPhi);

	// Check which keys are down
    if (keys['w' - 'a'] == 1) {
    	wanderer->rotateLeftWheel(-0.2f);
    	wanderer->rotateRightWheel(-0.2f);
    	wanderer->move(wanderer->getX() + sin(wanderer->getTheta()) * 0.3,
					surfacePoints[(int((wanderer->getX() + 50) / 100 * bezierCurve::getResolution()) * bezierCurve::getResolution() + int((wanderer->getZ() + 50) / 100 * bezierCurve::getResolution()))].getY(),
                    wanderer->getZ() + cos(wanderer->getTheta()) * 0.3);
    } if (keys['s' - 'a'] == 1) {
    	wanderer->rotateLeftWheel(0.2f);
    	wanderer->rotateRightWheel(0.2f);
        wanderer->move(wanderer->getX() + -sin(wanderer->getTheta()) * 0.3,
					surfacePoints[(int((wanderer->getX() + 50) / 100 * bezierCurve::getResolution()) * bezierCurve::getResolution() + int((wanderer->getZ() + 50) / 100 * bezierCurve::getResolution()))].getY(),
                    wanderer->getZ() + -cos(wanderer->getTheta()) * 0.3);
    } if (keys['a' - 'a'] == 1) {
    	wanderer->rotate(wanderer->getTheta() + 0.03f, wanderer->getPhi());
    	wanderer->rotateLeftWheel(0.05);
    	wanderer->rotateRightWheel(-0.05);
    	fpcamera.updateOrientation(fpcamera.getLength(), fpcamera.getTheta() - 0.03f, fpcamera.getPhi());
    } if (keys['d' - 'a'] == 1) {
        wanderer->rotate(wanderer->getTheta() - 0.03f, wanderer->getPhi());
    	wanderer->rotateLeftWheel(-0.05);
    	wanderer->rotateRightWheel(0.05);
    	fpcamera.updateOrientation(fpcamera.getLength(), fpcamera.getTheta() + 0.03f, fpcamera.getPhi());
    }

    // Move freecam
    if (!camera.arcBallEnabled() && (keys['i' - 'a'] == 1 || keys['j' - 'a'] == 1 || keys['k' - 'a'] == 1 || keys['l' - 'a'] == 1)) {
        float dirX = camera.getDirX();
        float dirY = camera.getDirY();
        float dirZ = camera.getDirZ();

        if (keys['k' - 'a'] == 1) camera.change_pos(dirX, dirY, dirZ);
        if (keys['i' - 'a'] == 1) camera.change_pos(-dirX, -dirY,-dirZ);
        if (keys['j' - 'a'] == 1) camera.change_pos(0,0,0);
        if (keys['l' - 'a'] == 1) camera.change_pos(0, 0, 0);
    }

    // Check car bounds
    wanderer->move(wanderer->getX() < -cityLength + 5 ? -cityLength + 5 : wanderer->getX(),
                wanderer->getY(),
                wanderer->getZ() < -cityLength + 5 ? -cityLength + 5 : wanderer->getZ());
    wanderer->move(wanderer->getX() > cityLength - 5 ? cityLength - 5 : wanderer->getX(),
                wanderer->getY(),
                wanderer->getZ() > cityLength - 5 ? cityLength - 5 : wanderer->getZ());

	// Update follower positions
	Direction tangent = heroPath1.getArcTanget();
	Point follower = heroPath1.getArcCordinate();
	fol1->move(wanderer->getX() + follower.getX(), wanderer->getY() + follower.getY(), wanderer->getZ() + follower.getZ());
	fol1->rotate(tangent.getTheta(), tangent.getPhi());

	tangent = heroPath2.getTanget();
	follower = heroPath2.getNextCordinate();
	fol2->move(wanderer->getX() + follower.getX(), wanderer->getY() + follower.getY(), wanderer->getZ() + follower.getZ());
	fol2->rotate(tangent.getTheta(), tangent.getPhi());

//	std::cout << tangent.getTheta() << " " << tangent.getPhi() << endl;

    // Update camera and redraw
    antikythera->animate();
    diomedes->animate();
    asterion->animate();

	// Update Cameras
    camera.updateCarPosition(*camerafollower);
    fpcamera.updatePosition(camerafollower->getX(), camerafollower->getY() + 5, camerafollower->getZ(), camerafollower->getDirX(), camerafollower->getDirY(), camerafollower->getDirZ());
	glutPostRedisplay();
	glutTimerFunc(20, myTimer, 0);
}

// cameraSelect() //////////////////////////////////////////////////////////////
//
//  Handles camera select menu events.
//
////////////////////////////////////////////////////////////////////////////////
void cameraSelect(int value) {
	switch (value) {
	// Switch to ArcBall
	case 0:
		camera.enableArcBallCam(); 
		glutPostRedisplay();
		break;

	// Switch to FreeCam
	case 1:
		camera.enableFreeCam();
		glutPostRedisplay();
		break;

	// Show/Hide First Person Camera
	case 2:
		displayFPCamera = !displayFPCamera;
		break;
	}
}

// heroSelect() /////////////////////////////////////////////////////////////////
//
//  Handles hero select menu events.
//
////////////////////////////////////////////////////////////////////////////////
void heroSelect(int value) {
	switch (value) {
	// Antikythera
	case 0:
		camerafollower = antikythera;
		glutPostRedisplay();
		break;

	// Asterion
	case 1:
		camerafollower = asterion;
		glutPostRedisplay();
		break;

	// Diomedes
	case 2:
		camerafollower = diomedes;
		glutPostRedisplay();
		break;
	}
}

// myMenu() //////////////////////////////////////////////////////////////////////
//
//  Handles main menu events.
//
////////////////////////////////////////////////////////////////////////////////
void myMenu(int value) {
	switch (value) {
	// Quit
	case 0:
		exit(0);
	}
}

// () //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Does not process command line arguments.
//
////////////////////////////////////////////////////////////////////////////////
int main (int argc, char **argv) {
    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Guild Wars");


    InputReader reader("input/infile.txt");
    heroPath1 = reader.getHeroPath();
	heroPath2 = reader.getHeroPath();
	surfacePoints = reader.getPoints();

    // initialize the hero vehicles
    antikythera = new Antikythera();
    diomedes = new Diomedes();
    asterion = new Asterion();

    // move the wanderer vehicles
    diomedes->move(10, 0, 0);
    diomedes->rotate(0, M_PI / 2);
	// move the hero vehicles
	for (int i = 0; i < 300; i++) heroPath1.getArcCordinate();		// offsets the cars
	Point init = heroPath1.getArcCordinate();
    antikythera->move(init.getX(), init.getY(), init.getZ());
    antikythera->rotate(0, M_PI / 2);
	init = heroPath2.getNextCordinate();
    asterion->move(init.getX(), init.getY(), init.getZ());
    asterion->rotate(0, M_PI / 2);

    // setup wanderer and camera follower
    wanderer = diomedes;
    camerafollower = diomedes;
	fol1 = asterion;
	fol2 = antikythera;

    // give the camera a scenic starting point.
    camera.updateOrientation(50.f, 0.f, M_PI * 3.f / 4.f);
    camera.updateCarPosition(*camerafollower);
    camera.updateUpVector(0, 1, 0);

    // give the fpcamera a scenic starting point
    fpcamera.enableFreeCam();
    fpcamera.updateUpVector(0, 1, 0);

    // initialize the popup menus
    int cselect = glutCreateMenu(cameraSelect);
    glutAddMenuEntry("ArcBall Camera", 0);
    glutAddMenuEntry("Free Camera", 1);
    glutAddMenuEntry("Show/Hide 1st-Person Camera", 2);

    int hselect = glutCreateMenu(heroSelect);
    glutAddMenuEntry("Antikythera", 0);
    glutAddMenuEntry("Asterion", 1);
    glutAddMenuEntry("Diomedes", 2);

    glutCreateMenu(myMenu);
    glutAddSubMenu("Camera Selection", cselect);
    glutAddSubMenu("Hero Selection", hselect);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // register callback functions...
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutKeyboardFunc(normalKeysDown);
    glutKeyboardUpFunc(normalKeysUp);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resizeWindow);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotion);
	glutTimerFunc(0, myTimer, 0); 

    // do some basic OpenGL setup
    initScene();

    // hit the stopwatch
    struct timeval tp;
	gettimeofday(&tp, NULL);
	start_millis = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}


