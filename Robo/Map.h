/* 
 * File:   Map.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:50 AM
 */

#ifndef MAP_H
#define	MAP_H
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Map {
private:
    char* _mapFile;
    unsigned float _robotSize,_mapResolutionCM,_gridResolutionCM;
    unsigned _width, _height;
    vector<unsigned char> _image;
    vector< vector<int> > _grid;
public:
    Map(char* parameters);
    Map(const Map& orig);
    virtual ~Map();

};

#endif	/* MAP_H */

