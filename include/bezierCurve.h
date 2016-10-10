#ifndef curve_header
#define curve_header

#include"ControlPoint.h"
#include"Point.h"
#include"drawable.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


class bezierCurve : public drawable {

    public:
    bezierCurve();
    bezierCurve(vector<ControlPoint>& pointy);
    bezierCurve(float r, float g, float b);
    void draw();
    void addPoint(ControlPoint pointy);
    void setPos(float x, float y, float z);
    void setLineColor(float r, float g, float b);
    void setCageColor(float r, float g, float b);
    void tooglePointVis();
    void toogleCurveVis();
    unsigned int getSize();
    Point getNextCordinate();
    void arcLengthParam();
    
    private:
    void setDefaults();
    float lineR,lineG,lineB;
    float cageR,cageG,cageB;
    Point evaluateBezierCurve( ControlPoint p0, ControlPoint p1, ControlPoint p2, ControlPoint p3, float t );
    vector<ControlPoint> controlPoints;
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