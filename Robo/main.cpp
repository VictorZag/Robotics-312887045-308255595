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
#include "PathPlanner.h"
#include "WaypointsManager.h"

using namespace PlayerCc;
using namespace std;


int main()
{
        Map m((char*)"parameters.txt");
        PathPlanner p(m);
        WaypointsManager wm(p.getGoalNode(),floor(m.getStartLocationX()/m.getGridResolutionPix()),floor(m.getStartLocationY()/m.getGridResolutionPix()));
//	Robot robot("localhost", 6665);
	return 0;
}




