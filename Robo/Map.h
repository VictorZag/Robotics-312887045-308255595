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
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "lodepng.h"
#include "Parameters.h"

using namespace std;

class Map {
private:
    
    unsigned _width, _height;
    vector<unsigned char> _image;
    vector<unsigned char> _blownImage;
    vector< vector<int> > _grid;
    
    void loadImage(const char* filename);
    void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
    void blowImage(float robotSize, float mapResolution);
    void createGrid(float mapResolution, float gridResolution);
    

    
public:
    Map(char* p_filePath);
    Map(const Map& orig);
    virtual ~Map();
    


};

#endif	/* MAP_H */

