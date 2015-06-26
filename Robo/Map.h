/* 
 * File:   Map.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:50 AM
 */

#ifndef MAP_H
#define	MAP_H
#include <vector>

class Map {
private:
    char* _mapSource;
    float _mapResolutionCM,_gridResolutionCM;
    unsigned _width, _height;
    vector<unsigned char> _image;
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();

};

#endif	/* MAP_H */

