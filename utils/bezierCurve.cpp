#include "../include/bezierCurve.h"

int bezierCurve::resolution = 300;

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

float bezierCurve::distance(Point& start, Point& end){
    Direction vec(start,end);
    return vec.getLength();
}

void bezierCurve::setDefaults(){
    lineR = 0;
    lineG = 0;
    lineB = 1;

    cageR = 1;
    cageG = 1;
    cageB = .2;

    resolution = 300;
    
    arcLocation = 0;
    
    curveVis = false;
    pointsVis = false;
    cageVis = false;

}

void bezierCurve::addPoint(Point pointy){
    controlPoints.push_back(pointy);
    caculatePoints();
}


Point bezierCurve::linearInterpolation(Point a, Point b, float t){
	Point p = (1-t)*a + t*b;
	return p;
}

Point bezierCurve::evaluateBezierCurve( Point p0, Point p1, Point p2, Point p3, float t ) {
    Point q0 = linearInterpolation(p0,p1,t);
    Point q1 = linearInterpolation(p1,p2,t);
    Point q2 = linearInterpolation(p2,p3,t);
    Point r0 = linearInterpolation(q0,q1,t);
    Point r1 = linearInterpolation(q1,q2,t);
    Point p =  linearInterpolation(r0,r1,t);
    return p;
}


unsigned int bezierCurve::getSize(){
    return controlPoints.size();
}

void bezierCurve::caculatePoints(){
    curvePoints.clear();
    location = 0;
    //std::cout<<"BEGIN"<<std::endl; 
    float step=1.0/resolution;
    for(unsigned int start = 0; start +4 <= controlPoints.size(); start += 3){
        for(float t = 0; t <= 1; t += step){
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

Point bezierCurve::getArcCordinate(){
    if (arcLengthCurve.empty()){
        arcLengthParam();
    }
    if (arcLocation >= arcLengthCurve.size()){
        arcLocation = 0;
    }
    return arcLengthCurve[arcLocation++];
}

void bezierCurve::arcLengthParam(){
	float targetLength = distance(curvePoints[1], curvePoints[0]);
	unsigned int pointNum = curvePoints.size();
        double currentLength = 0;
        Point lastPoint;
	arcLengthCurve.push_back(curvePoints[0]);
	arcLengthCurve.push_back(curvePoints[1]);
        lastPoint = curvePoints[1];
        unsigned int point = 2;
        bool done = false;
	while (!done){
            float segmentLength = distance(lastPoint,curvePoints[point]);
            if (targetLength == (segmentLength + currentLength)){
                arcLengthCurve.push_back(curvePoints[point]);
                currentLength = 0;
                lastPoint = curvePoints[point++];
            }
            else if ((segmentLength + currentLength) < targetLength) {
                currentLength += segmentLength;
                lastPoint = curvePoints[point++];
            }
            else {
                float neededLength = targetLength - currentLength;
                float t = neededLength / segmentLength;
                //std::cout<<"State[ "<<"Segment:("<<point-1<<", "<<point<<")  Length:("<<targetLength<<", "<<currentLength<<", "<<segmentLength<<", "<<neededLength<<")  T: "<<t<<" ]"<<std::endl;
                Point p = linearInterpolation(lastPoint,curvePoints[point],t);
                arcLengthCurve.push_back(p);
                currentLength = 0;
                lastPoint = p;
            }
            if (point >= pointNum){
                done = true;
            }
        }
}


bool bezierCurve::threshold(float a, float b){
    double temp = a-b;
    temp *= temp;
    //std::cout<<"Comparing: "<<a<<",  "<<b<<", and r^2 of "<<temp<<std::endl;
    if (temp < .00001){
        return true;
    }
    return false;
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
cageVis = false; curveVis = true;
    if(cageVis){
        glPushMatrix();
        glDisable(GL_LIGHTING);

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
        cloth.setCopper();
        glLineWidth(3.0f);
        glBegin(GL_LINE_STRIP);
        for(unsigned int i = 0; i < curvePoints.size(); ++i){
            glVertex3fv(curvePoints[i].getPos());
        }
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();
}


Direction bezierCurve::getTanget(){
    Point a,b;
    if (location == (0)){
        a = curvePoints[curvePoints.size()-1];
    }
    else {
        a = curvePoints[location-1];
    }
    /*
    if (location == (curvePoints.size() -1)){
        b = curvePoints[0];
    }
    else {
        b = curvePoints[location + 1];
    }
    */
    b = curvePoints[location];
    Direction d (b,a);
    return d;
}


Direction bezierCurve::getArcTanget(){
    if (arcLengthCurve.empty()){
        arcLengthParam();
    }
    Point a,b;
    if (arcLocation == 0){
        a = arcLengthCurve[arcLengthCurve.size()-1];
    }
    else {
        a = arcLengthCurve[arcLocation - 1];
    }
    if (arcLocation == arcLengthCurve.size()-1){
        b = arcLengthCurve[0];
    }
    else {
        b = arcLengthCurve[arcLocation + 1];
    }
    Direction d(b,a);
	return d;
}
