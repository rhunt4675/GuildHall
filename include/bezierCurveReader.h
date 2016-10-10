#include<string>
#include"bezierCurve.h"
#include <fstream>          // we'll use ifstream   
#include <string>           // for, well strings!
#include <vector>           // and vectors (the storage container, not directional)
#include<iostream>

#ifdef _WIN32
    #include <windows.h>
	#include <tchar.h>
	#include <winbase.h>
#else
	//POSIX Includes
	#include <sys/stat.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <dirent.h>
#endif

using namespace std;

class bezierCurveReader{
    public:
    vector<bezierCurve> readFolder(string path); //Made to process fancy formated inputs
    bezierCurve readFile(string path); //Requiers that I finish making the fancy input parcer
    vector<bezierCurve> read(string path); //Thought that we had to do that for this assigment but I was wrong
    bezierCurve simpleRead(string path); //Legacy function that can generate a bezierCurve object off the lab03 format

    private:
    
    ControlPoint genPoint(string& line);
    void setControl(string line);
    float byteToFloat(int byte);
    float pointR,pointG,pointB;
    float curveR,curveG,curveB;
    bool quickCompare(string &longer, string &shorter, size_t &length);
    bool isFolder(string path);
    void getFiles(string path, vector<string> &files);
};

