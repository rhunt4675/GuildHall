#include "../include/bezierCurveReader.h"
using namespace std;

vector<bezierCurve> bezierCurveReader::readFolder(string path){
    vector<string> files;
    getFiles(path, files);
    vector<bezierCurve> output;
    for (unsigned int i = 0; i < files.size(); ++i){
        output.push_back(readFile(files[i]));
    }
    return output;
}

bezierCurve bezierCurveReader::readFile(string path){
    ifstream input_file(path);
    string::size_type sz;
    if (input_file.is_open()){
        string line;
        getline(input_file,line);
        //int line_num = stoi(line,&sz);
        bezierCurve stub;
        return stub;
        /*
         * TODO fancy Processing
         for(int i = 0; i < line_num; ++i){
         getline(input_file,line);
         if (quickCompare(line, "point", 5){
         Point pointy = genPoint(line.substr(6,line.length());
         }
         else if (quickCompare(line, "control",6){
         setControl(line);
         }
         else {
         cout<<"Line Skiped due to bad formating"<<endl;
         }
         }
         */
    }
    else {
        cout<<"File "<<path<<" could not be opened or does not exist. File was skiped"<<endl;
        bezierCurve stub;
        return stub;
    }
}

vector<bezierCurve> bezierCurveReader::read(string path){
    vector<bezierCurve> curves;
        if (isFolder(path)){
            curves = readFolder(path);
        }
        else {
            curves.push_back(readFile(path));
        }
    return curves;
}


bezierCurve bezierCurveReader::simpleRead(string path){
    bezierCurve curie;
    ifstream input_file(path);
    string::size_type sz;
    if (input_file.is_open()){
        string line;
        getline(input_file,line);
        int line_num = stoi(line,&sz);
        for(int i = 0; i < line_num; ++i){
            getline(input_file,line);
            curie.addPoint(genPoint(line));
        }
    }
    return curie;
}

ControlPoint bezierCurveReader::genPoint(string& line){
    string::size_type sz;
    vector<string> col;
    for(size_t pos = line.find(','); pos != string::npos; pos = line.find(',')){
        col.push_back(line.substr(0,pos));
        line = line.substr(pos + 1, line.length());
    }
    col.push_back(line);
    if (col.size() != 3){
        cout<<"Error file is formated wrongly"<<endl;
        exit(-1);
    }
    else {
        int x = stoi(col[0],&sz);   
        int y = stoi(col[1],&sz);   
        int z = stoi(col[2],&sz);
        //cout<<x<<", "<<y<<", "<<z<<endl;
        ControlPoint p(x,y,z);
        return p;
    }
}

void bezierCurveReader::setControl(string line){

}

bool bezierCurveReader::quickCompare(string &longer, string &shorter, size_t &length){
    for (size_t i = 0; i < length; ++i){
        if (longer[i] != shorter[i]){
            return false;
        }
    }
    return true;
}

void  bezierCurveReader::getFiles(string path, vector<string> &files){
}


bool bezierCurveReader::isFolder(string path){
    return false;  
}

float bezierCurveReader::byteToFloat(int byte){
    float output = byte;
    output /= 255;
    return output;
}


