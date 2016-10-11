#ifndef curve_header
#define curve_header

#include"Point.h"
#include"drawable.h"
#include <vector>
#include <string>
#include <iostream>

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

using namespace std;


class bezierCurve : public drawable {

    public:
    bezierCurve();
    bezierCurve(vector<Point>& pointy);
    bezierCurve(float r, float g, float b);
    void draw();
    void addPoint(Point pointy);
    void setPos(float x, float y, float z);
    void setLineColor(float r, float g, float b);
    void setCageColor(float r, float g, float b);
    void tooglePointVis();
    void toogleCurveVis();
    unsigned int getSize();
    Point getNextCordinate();
    void arcLengthParam();
    int getResolution();
    
    private:
    void setDefaults();
    float lineR,lineG,lineB;
    float cageR,cageG,cageB;
    Point evaluateBezierCurve( Point p0, Point p1, Point p2, Point p3, float t );
    vector<Point> controlPoints;
    int order;
    vector<Point> curvePoints;
    unsigned int location;
    void caculatePoints();
    int resolution;
    
    protected:
    bool pointsVis;
    bool cageVis;
    bool curveVis;

};


#endif
