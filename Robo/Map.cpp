/* 
 * File:   Map.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:50 AM
 */

#include "Map.h"


Map::Map(char* p_filePath) {
    ConfigurationManager cm (p_filePath);
    loadImage("roboticLabMap.png");
    blowImage(cm.GetRobotSize(),cm.GetMapResolutionCM());
    float gridResolutionPix = cm.GetGridResolutionCM() / cm.GetMapResolutionCM();
    createGrid(gridResolutionPix);
//    for (int i =0; i<_grid.size();i++)
//    {
//        for(int j =0; j<_grid[0].size();j++)
//        {
//            for (int a =i*4; a<(i+1)*4;a++)
//            {
//                for (int b =j*4; b<(j+1)*4;b++)
//                {
//                    if (_grid[i][j] == 1)
//                    {
//                        _blownImage[((a*_width)+b)*4]=0;
//                        _blownImage[((a*_width)+b)*4+1]=0;
//                        _blownImage[((a*_width)+b)*4+2]=0;
//                        _blownImage[((a*_width)+b)*4+3]=255;
//                    }
//                }
//            }
//        }
//    }
    
    GridNode* goalNode;
    goalNode = aStar(cm.GetGridResolutionCM(), floor(cm.GetStartLocationY()/gridResolutionPix), floor(cm.GetStartLocationX()/gridResolutionPix), floor(cm.GetGoalLocationY()/gridResolutionPix), floor(cm.GetGoalLocationX()/gridResolutionPix));
    std::cout << "------------------";
    while (goalNode->place.x!=floor(cm.GetStartLocationY()/gridResolutionPix) || goalNode->place.y!=floor(cm.GetStartLocationX()/gridResolutionPix))
    {
        std::cout << goalNode->place.x << " " << goalNode->place.y << "\n";
        for (int a =goalNode->place.x*4; a<(goalNode->place.x+1)*4;a++)
            {
                for (int b =goalNode->place.y*4; b<(goalNode->place.y+1)*4;b++)
                {
                    _image[((a*_width)+b)*4]=0;
                    _image[((a*_width)+b)*4+1]=0;
                    _image[((a*_width)+b)*4+2]=255;
                    _image[((a*_width)+b)*4+3]=255;
                }
            }
        goalNode = goalNode->parent;
    }
    for (int a =cm.GetStartLocationY(); a<(cm.GetStartLocationY()+4);a++)
            {
                for (int b =cm.GetStartLocationX(); b<(cm.GetStartLocationX()+4);b++)
                {
                    _image[((a*_width)+b)*4]=0;
                    _image[((a*_width)+b)*4+1]=255;
                    _image[((a*_width)+b)*4+2]=0;
                    _image[((a*_width)+b)*4+3]=255;
                }
            }
    for (int a =cm.GetGoalLocationY(); a<(cm.GetGoalLocationY()+4);a++)
            {
                for (int b =cm.GetGoalLocationX(); b<(cm.GetGoalLocationX()+4);b++)
                {
                    _image[((a*_width)+b)*4]=255;
                    _image[((a*_width)+b)*4+1]=0;
                    _image[((a*_width)+b)*4+2]=0;
                    _image[((a*_width)+b)*4+3]=255;
                }
            }
    saveImage("test1.png",_image,_width,_height);
}

Map::Map(const Map& orig) {
   
}

Map::~Map() {
}

void Map::loadImage(const char* filename)
{
  //decode
  unsigned error = lodepng::decode(_image, _width, _height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void Map::saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}
void Map::blowImage(float robotSize, float mapResolution)
{
    
    for (unsigned int i = 0; i < _width * _height * 4; i+=1)
    {
       _blownImage.push_back((unsigned char)255);
    }
    unsigned int blowWallBy = ((robotSize/mapResolution) + 1) / 2;
    for (unsigned int i = 0; i < _height; i++)
    {
        for (unsigned int j = 0; j < _width; j++)
        {
            if(_image[((i*_width)+j)*4]==0)
            {
                for(unsigned int a = std::max((unsigned int)0,i-blowWallBy); a <= std::min(_height-1,i+blowWallBy) ; a++)
                {
                    for(unsigned int b = std::max((unsigned int)0,j-blowWallBy); b <= std::min(_width-1,j+blowWallBy) ; b++)
                    {
                        _blownImage[((a*_width)+b)*4] = 0;
                        _blownImage[((a*_width)+b)*4 + 1] = 0;
                        _blownImage[((a*_width)+b)*4 + 2] = 0;
                        _blownImage[((a*_width)+b)*4 + 3] = 255;
                    }
                }
            }
        }

    }
}
void Map::createGrid(float gridResolutionPix)
{
    int rows = _height / gridResolutionPix;
    int cols = _width / gridResolutionPix;
    for (unsigned int r=0; r<rows; r++)
    {
        vector<int> gridRow(cols);
        for (unsigned int c=0; c<cols; c++)
        {
            int occupied = 0;
            for (unsigned int ir=r*gridResolutionPix; ir<(r+1)*gridResolutionPix && occupied == 0; ir++)
            {
                for (unsigned int ic=c*gridResolutionPix; ic<(c+1)*gridResolutionPix && occupied == 0; ic++)
                {
                    if(_blownImage[((ir*_width)+ic)*4] == 0)
                    {
                        occupied = 1;
                    }
                }            
            }
            gridRow[c]=occupied;
        }
        _grid.push_back(gridRow);
    }
}
float Map::heuristic_cost_estimate(Location start, Location goal)
{
    float dx = start.x-goal.x;
    float dy = start.y-goal.y;
    return sqrt(dx * dx + dy * dy);
}
int Map::minGScoreL(vector<GridNode*> open)
{
    float minG=open[0]->g_score;
    int minI=0;
    for(int i = 1; i < open.size(); i++)
    {
        if(open[i]->g_score < minG)
        {
            minI = i;
            minG = open[i]->g_score;
        }
    }
    return minI;
}
int Map::getNodeByL(vector<GridNode*> open,unsigned int nx, unsigned int ny)
{
    for(int i = 1; i < open.size(); i++)
    {
        if(open[i]->place.x == nx && open[i]->place.y == ny)
        {
            return i;
        }
    }
}
GridNode* Map::aStar(float gridResolution, float startX, float startY, float goalX, float goalY)
{
    Location goal;
    goal.x=goalX;
    goal.y=goalY;
    unsigned int rows = _grid.size();
    unsigned int cols = _grid[0].size();
    int dontCheck[rows][cols];
    float gCheck[rows][cols];
    for (unsigned int r=0; r<rows; r++)
    {
        for (unsigned int c=0; c<cols; c++)
        {
            dontCheck[r][c] = _grid[r][c];
            gCheck[r][c] = -1;
            if (_grid[r][c] == 1)
            {
                std::cout << r << " " << c << "\n";
            }
        }
    }
    GridNode* startNode = new GridNode;;
    startNode->place.x=startX;
    startNode->place.y=startY;
    startNode->t_score=0;
    startNode->g_score=heuristic_cost_estimate(startNode->place,goal);
    gCheck[(int)startX][(int)startY] = startNode->g_score;
    vector<GridNode*> openSet;
    openSet.push_back(startNode);
    while(!openSet.empty())
    {
        int minGLocation = minGScoreL(openSet);
        GridNode* current = openSet[minGLocation];
        openSet.erase(openSet.begin()+minGLocation);
        dontCheck[current->place.x][current->place.y]=1;
        for (unsigned int neighborX=std::max((unsigned int)0,current->place.x-1);neighborX<=std::min(current->place.x+1,rows-1);neighborX++)
        {
            for (unsigned int neighborY=std::max((unsigned int)0,current->place.y-1);neighborY<=std::min(current->place.y+1,cols-1);neighborY++)
            {
                if(dontCheck[neighborX][neighborY] == 0)
                {
                    GridNode* neighbor = new GridNode;
                    neighbor->parent=current;
                    neighbor->place.x=neighborX;
                    neighbor->place.y=neighborY;
                    if(neighborX == goalX && neighborY == goalY)
                    {
                        return neighbor;
                    }
                    neighbor->t_score=current->t_score;
                    if(neighborX==current->place.x || neighborY==current->place.y)
                    {
                        neighbor->t_score+=gridResolution;
                    }
                    else
                    {
                        neighbor->t_score+=sqrt(gridResolution*gridResolution*2);
                    }
                    neighbor->g_score=neighbor->t_score+heuristic_cost_estimate(neighbor->place,goal);
                    if(gCheck[neighborX][neighborY] == -1)
                    {
                        gCheck[neighborX][neighborY] = neighbor->g_score;
                        openSet.push_back(neighbor);
                    }
                    else if (neighbor->g_score < gCheck[neighborX][neighborY])
                    {
                        gCheck[neighborX][neighborY] = neighbor->g_score;
                        int existingNodeI = getNodeByL(openSet,neighborX,neighborY);
                        openSet[existingNodeI]->t_score = neighbor->t_score;
                        openSet[existingNodeI]->g_score = neighbor->g_score;
                        openSet[existingNodeI]->parent = neighbor->parent;
                                
                    }
                }
            }
        }
        
        
    }
//    return &startNode;
}

