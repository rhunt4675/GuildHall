#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <string>
#include <sstream>
#include "bezierCurve.h"
#include "Point.h"
#include <fstream>
#include <vector>
#include <iostream>

class InputReader {
	private:
		bezierCurve petPath;
		bezierCurve heroPath;
		struct Object {
			string type;
			Point location;
			float xDir, yDir, zDir;
			float size;
		};
		vector<Object> objs;
		vector<Point> surfacePoints;

		void calcSurface(vector<Point>);

	public:
		bezierCurve getHeroPath() {return heroPath;}
		vector<Point> getPoints() {return surfacePoints;}
		InputReader(string infile);
	
};

#endif
