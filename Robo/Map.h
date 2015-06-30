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

class Location
{
public:
    unsigned int x;
    unsigned int y;
};

class GridNode
{
public:
    Location place;
    float t_score;
    float g_score;
    GridNode* parent;
};

class Map {
private:
    
    unsigned _width, _height;
    vector<unsigned char> _image;
    vector<unsigned char> _blownImage;
    vector< vector<int> > _grid;
    
    void loadImage(const char* filename);
    void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
    void blowImage(float robotSize, float mapResolution);
    void createGrid(float gridResolutionPix);
    float heuristic_cost_estimate(Location start, Location goal);
    int minGScoreL(vector<GridNode*> open);
    int getNodeByL(vector<GridNode*> open,unsigned int nx, unsigned int ny);
    GridNode* aStar(float gridResolution, float startX, float startY, float goalX, float goalY);    

    
public:
    Map(char* p_filePath);
    Map(const Map& orig);
    virtual ~Map();
    


};

#endif	/* MAP_H */

