#include "../include/InputReader.h"

InputReader::InputReader(string infile) {
	ifstream inputData(infile);
	string line;
	stringstream ss;

	// Gets surface of world
	getline(inputData, line);
	int numSurfaces = stoi(line);
	vector<Point> surfacePoints;
	for (int i = 0; i < numSurfaces; i++) {
		for (int j = 0; j < 16; j++) {
			getline(inputData, line);
			ss.clear(); ss.str("");
			ss << line;
			int x, y, z;
			ss >> x >> y >> z;
			surfacePoints.push_back(Point(x, y, z));
		}
	}
	calcSurface(surfacePoints);

	// Gets pet curve
	getline(inputData, line);
	int numPoints = stoi(line);
	vector<Point> petCurvePoints;
	for (int j = 0; j < numPoints; j++) {
		getline(inputData, line);
		ss.clear(); ss.str("");
		ss << line;
		int x, y, z;
		ss >> x >> y >> z;
		petCurvePoints.push_back(Point(x, y, z));
	}
	petPath = bezierCurve(petCurvePoints);

	// Gets hero curve
	getline(inputData, line);
	numPoints = stoi(line);
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

	inputData.close();
}


void InputReader::calcSurface(vector<Point> points) {
	surfacePoints.clear();
	for (unsigned int i = 0; i < points.size() / 16; i++) {		// for every surface
		bezierCurve curves[4];
		for (int j = 0; j < 4; j++) {
			vector<Point> p;
			for (int k = 0; k < 4; k++) {
				p.push_back(points[i * 16 + k]);
			}
			curves[j] = bezierCurve(p);
		}
		for (int j = 0; j < curves[0].getResolution(); j++) {
			vector<Point> p;
			for (int k = 0; k < 4; k++) {
				p.push_back(curves[k].getNextCordinate());
			}
			bezierCurve curve(p);
			for (int k = 0; k < curve.getResolution(); k++) {
				surfacePoints.push_back(curve.getNextCordinate());
			}
		}
	}
}
