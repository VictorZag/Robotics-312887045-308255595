/* 
 * File:   Map.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:50 AM
 */

#ifndef MAP_H
#define	MAP_H
#include <stdlib.h>
#include <vector>
#include<fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Map {
private:
    std::string _mapFile;
    float _robotSize,_mapResolutionCM,_gridResolutionCM;
    unsigned _width, _height;
    vector<unsigned char> _image;
    vector< vector<int> > _grid;
    
    // Value-Defintions of the different String values
    enum StringValue { map,
                        startLocation,
                        goal,
                        robotSize,
                        MapResolutionCM,
                        GridResolutionCM };
                          
    // Map to associate the strings with the enum values
    static std::map<std::string, StringValue> s_mapStringValues;
    
public:
    Map(char* parameters);
    Map(const Map& orig);
    unsigned int str2int(const char* str, int h = 0);
    virtual ~Map();

};

#endif	/* MAP_H */

