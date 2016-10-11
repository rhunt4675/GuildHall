#include "../include/InputReader.h"

InputReader::InputReader(string infile) {
	ifstream inputData(infile);
	string line;
	stringstream ss;

	// Gets surface of world
	getline(inputData, line);
	int numSurfaces = atoi(line.c_str());
	vector<Point> points;
	for (int i = 0; i < numSurfaces; i++) {
		for (int j = 0; j < 16; j++) {
			getline(inputData, line);
			ss.clear(); ss.str("");
			ss << line;
			int x, y, z;
			ss >> x >> y >> z;
			points.push_back(Point(x, y, z));
		}
	}
	calcSurface(points);

	// Gets hero curve
	getline(inputData, line);
	int numPoints = atoi(line.c_str());
	vector<Point> heroCurvePoints;
	for (int j = 0; j < numPoints; j++) {
		getline(inputData, line);
		ss.clear(); ss.str("");
		ss << line;
		int x, y, z;
		ss >> x >> y >> z;
		heroCurvePoints.push_back(Point(x, y, z));
	}
	heroPath = bezierCurve(heroCurvePoints);
	
	// TODO: Gets object info
	getline(inputData, line);
	int numObjs = atoi(line.c_str());
	objs.clear();
	for (int j = 0; j < numObjs; j++) {
		getline(inputData, line);
		ss.clear(); ss.str("");
		ss << line;
		Object o;
		float x, y, z;
		ss >> o.type >> x >> y >> z >> o.size;
		Point p(x, y, z);
		o.location = p;
		objs.push_back(o);
	}

	inputData.close();
}


void InputReader::calcSurface(vector<Point> points) {
	surfacePoints.clear();
	for (unsigned int i = 0; i < points.size() / 16; i++) {		// for every surface
		bezierCurve curves[4];
		for (int j = 0; j < 4; j++) {
			vector<Point> p;
			for (int k = 0; k < 4; k++) {
				p.push_back(points[i * 16 + j * 4 + k]);
			}
			curves[j] = bezierCurve(p);
		}
		for (int j = 0; j < bezierCurve::getResolution(); j++) {
			vector<Point> p;
			for (int k = 0; k < 4; k++) {
				p.push_back(curves[k].getNextCordinate());
			}
			bezierCurve curve(p);
			for (int k = 0; k < bezierCurve::getResolution(); k++) {
				surfacePoints.push_back(curve.getNextCordinate());
			}
		}
	}
}
