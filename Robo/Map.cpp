/* 
 * File:   Map.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:50 AM
 */

#include "Map.h"


Map::Map() {
    Parameters p ((char*)"parameters.txt");
    loadImage((const char*)p.GetMapFilePath());
    blowImage(p.GetRobotSize(),p.GetMapResolutionCM());
}

Map::Map(const Map& orig) {
   
}

Map::~Map() {
}

void loadImage(const char* filename)
{
  //decode
  unsigned error = lodepng::decode(_image, _width, _height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}
void blowImage(float robotSize, float mapResolution)
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
void createGrid()
{
    
}
