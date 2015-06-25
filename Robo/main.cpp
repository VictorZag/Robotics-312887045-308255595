/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "lodepng.h"

using namespace PlayerCc;
using namespace std;

std::vector<unsigned char> image; //the raw pixels
std::vector<unsigned char> newImage;
unsigned width, height;


//Example 1
//Decode from disk to raw pixels with a single function call
void loadImage(const char* filename)
{
  //decode
  unsigned error = lodepng::decode(image, width, height, filename);
  lodepng::decode(newImage, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

//Example 1
//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int main()
{
        const char* filename = "roboticLabMap.png";
	loadImage(filename);

	cout << "width: " << width << ", height: " << height << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << (int)image[i] << " ";
	}
	cout << endl;

	//  Change the first line to black
	/*for (unsigned int i = 0; i < width * 4 * 5; i+=4)
	{
		image[i] = 0;
		image[i + 1] = 0;
		image[i + 2] = 0;
		image[i + 3] = 255;
	}*/
	for (unsigned int i = 0; i < width * height * 4; i+=1)
	{
		newImage[i] = 255;
	}
        // blowBy= ((sizeofBOT/MAPrez)+1)/2
	unsigned int blowWallBy = ((30/2.5)+1)/2;
	for (unsigned int i = 0; i < width * height * 4; i+=4)
	{
		if(image[i]==0){
			for (unsigned a=i-width*4*blowWallBy; a<=i+width*4*blowWallBy; a+=width*4)
			{
				for (unsigned b=a-blowWallBy*4; b<=a+blowWallBy*4; b+=4)
				{
					newImage[b] = 0;
					newImage[b + 1] = 0;
					newImage[b + 2] = 0;
					newImage[b + 3] = 255;
				}
			}
		}
		
	}

	const char* newfile = "roboticLabMap2.png";
	saveImage(newfile, newImage, width, height);
        
	Robot robot("localhost", 6665);
	return 0;
}




