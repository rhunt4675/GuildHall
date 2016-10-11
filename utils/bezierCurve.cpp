#include "../include/bezierCurve.h"

bezierCurve::bezierCurve() {
    setDefaults();
}

bezierCurve::bezierCurve(vector<Point>& pointy) {
    controlPoints = pointy;
    caculatePoints();
    setDefaults();
}


bezierCurve::bezierCurve(float r, float g, float b) {
    setDefaults();

    lineR = r;
    lineG = g;
    lineB = b;
}

void bezierCurve::setDefaults(){
    lineR = 0;
    lineG = 0;
    lineB = 1;

    cageR = 1;
    cageG = 1;
    cageB = .2;

    resolution = 300;
    
    curveVis = false;
    pointsVis = false;
    cageVis = false;

}

void bezierCurve::addPoint(Point pointy){
    controlPoints.push_back(pointy);
    caculatePoints();
}


Point bezierCurve::evaluateBezierCurve( Point p0, Point p1, Point p2, Point p3, float t ) {
    Point q0 = (1-t)*p0 + t*p1;
    Point q1 = (1-t)*p1 + t*p2;
    Point q2 = (1-t)*p2 + t*p3;
    Point r0 = (1-t)*q0 + t*q1;
    Point r1 = (1-t)*q1 + t*q2;
    Point p =  (1-t)*r0 + t*r1;
    return p;
}


unsigned int bezierCurve::getSize(){
    return controlPoints.size();
}

void bezierCurve::caculatePoints(){
    curvePoints.clear();
    //std::cout<<"BEGIN"<<std::endl;
    float step=1.0/resolution;
    for(unsigned int start = 0; start + 4 <= controlPoints.size(); start += 3){
        for(float t = 0; t < 1; t += step){
            Point p = evaluateBezierCurve(controlPoints[start],controlPoints[start+1],controlPoints[start+2],controlPoints[start+3],t);
            //std::cout<<p.getX()<<", "<<p.getY()<<", "<<p.getZ()<<std::endl;
            curvePoints.push_back(p);
        }
    }
    //std::cout<<"END"<<std::endl;
}

Point bezierCurve::getNextCordinate(){
    if (location >= curvePoints.size()){
        location = 0;
    }
    return curvePoints[location++];
}

void arcLengthParam(){
    

}


void bezierCurve::tooglePointVis(){
    pointsVis = !pointsVis;
    cageVis = !cageVis;
}

void bezierCurve::toogleCurveVis(){
    curveVis = !curveVis;
}

void bezierCurve::draw(){
    glPushMatrix();
//    if(pointsVis){
//        for(unsigned int i = 0; i < controlPoints.size(); ++i){
//            controlPoints[i].draw();
//        }
//    }

    if(cageVis){
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glColor3f(cageR,cageG,cageB);
        glLineWidth(3.0f);	
        glBegin( GL_LINE_STRIP );
        for(unsigned int i = 0; i < controlPoints.size(); ++i){
            glVertex3fv(controlPoints[i].getPos());
        }
        glEnd();
        glEnable( GL_LIGHTING );
        glPopMatrix();

    }

    if(curveVis){
        glPushMatrix();
        glDisable( GL_LIGHTING );
        glColor3f(lineR,lineG,lineB);
        glLineWidth(3.0f);
        glBegin(GL_LINE_STRIP);
        for(unsigned int i = 0; i < curvePoints.size(); ++i){
            glVertex3fv(curvePoints[i].getPos());
        }
        glEnd();
        glEnable( GL_LIGHTING );
        glPopMatrix();
    }

    glPopMatrix();
}

int bezierCurve::getResolution() {
	return resolution;
}
