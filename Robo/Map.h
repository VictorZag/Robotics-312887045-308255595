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
#include <queue>
#include <math.h>
#include "lodepng.h"
#include "ConfigurationManager.h"


using namespace std;

class Map {
private:
    
    unsigned _width, _height;
    vector<unsigned char> _image;
    vector<unsigned char> _blownImage;
    vector< vector<int> > _grid;
    ConfigurationManager* _cm;
    
    void loadImage(const char* filename);
    void blowImage(float robotSize, float mapResolution);
    void createGrid(float gridResolutionPix);
    
    
public:
    Map(char* p_filePath);
    Map(const Map& orig);
    virtual ~Map();
    void saveImage(const char* filename, std::vector<unsigned char>& image ,unsigned width, unsigned height);
    unsigned getWidth();
    unsigned getHeight();
    vector<unsigned char> getImage();
    vector< vector<int> > getGrid();
    float getGridResolutionPix();
    float geGridResolution();
    float getStartLocationX();
    float getStartLocationY();
    float getGoalLocationX();
    float getGoalLocationY();
};

#endif	/* MAP_H */

