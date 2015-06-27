/* 
 * File:   Map.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:50 AM
 */

#include "Map.h"
#include "Parameters.h"


Map::Map(char* p_filePath) {
    Parameters p (p_filePath);
    loadImage(p.GetMapFilePath().c_str());
    blowImage(p.GetRobotSize(),p.GetMapResolutionCM());
    const char* newfile = "robo_section2.png";
    saveImage(newfile, _blownImage, _width, _height);
    createGrid(p.GetMapResolutionCM(),p.GetGridResolutionCM());
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
void Map::createGrid(float mapResolution, float gridResolution)
{
    float gridResolutionPix = gridResolution / mapResolution;
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
            gridRow.push_back(occupied);
        }
        _grid.push_back(gridRow);
    }
}
