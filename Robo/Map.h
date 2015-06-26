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
    
    unsigned _width, _height;
    vector<unsigned char> _image;
    vector< vector<int> > _grid;
    

    
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();

};

#endif	/* MAP_H */

