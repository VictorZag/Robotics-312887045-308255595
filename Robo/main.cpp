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
#include "Map.h"

using namespace PlayerCc;
using namespace std;


int main()
{
        Map m((char*)"parameters.txt");
	Robot robot("localhost", 6665);
	return 0;
}




