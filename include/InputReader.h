#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <string>
#include <sstream>
#include "bezierCurve.h"
#include "Point.h"
#include <fstream>
#include <vector>
#include <iostream>

struct Object {
	string type;
	Point location;
	float size;
};


class InputReader {
	private:
		bezierCurve petPath;
		bezierCurve heroPath;
		vector<Object> objs;
		vector<Point> surfacePoints;

		void calcSurface(vector<Point>);

	public:
		bezierCurve getHeroPath() {return heroPath;}
		vector<Point> getPoints() {return surfacePoints;}
		vector<Object> getObjects() {return objs;}
		InputReader(string infile);
	
};

#endif
