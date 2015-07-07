/* 
 * File:   Map.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:50 AM
 */

#include "Map.h"


Map::Map(char* p_filePath) {
    _cm = new ConfigurationManager(p_filePath);
    loadImage(_cm->GetMapFilePath().c_str());
    blowImage(_cm->GetRobotSize(),_cm->GetMapResolutionCM());
    createGrid(getGridResolutionPix());
}

Map::Map(const Map& orig) {
   _blownImage = orig._blownImage;
   _cm = orig._cm;
   _grid = orig._grid;
   _height = orig._height;
   _width = orig._width;
   _image = orig._image;
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
unsigned int Map::gridFromPix(float index)
{
    return floor(index / getGridResolutionPix());
}
float Map::pixFromGrid(unsigned int index)
{
    return index * getGridResolutionPix() + getGridResolutionPix() / 2;
}
unsigned Map::getWidth()
{
    return _width;
}
unsigned Map::getHeight()
{
    return _height;
}
vector<unsigned char> Map::getImage()
{
    return _image;
}
vector< vector<int> > Map::getGrid()
{
    return _grid;
}
float Map::getGridResolutionPix()
{
    return _cm->GetGridResolutionCM() / _cm->GetMapResolutionCM();
}
float Map::geGridResolution()
{
    return _cm->GetGridResolutionCM();
}
float Map::getStartLocationX()
{
    return _cm->GetStartLocationX();
}
float Map::getStartLocationY()
{
    return _cm->GetStartLocationY();
}
float Map::getGoalLocationX()
{
    return _cm->GetGoalLocationX();
}
float Map::getGoalLocationY()
{
    return _cm->GetGoalLocationY();
}