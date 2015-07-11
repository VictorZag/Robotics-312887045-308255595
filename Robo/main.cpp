/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <unistd.h>
#include "Robot.h"
#include "lodepng.h"
#include "Map.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"
#include "MoveForward.h"
#include "Turn.h"

#define PI 3.14159265

using namespace PlayerCc;
using namespace std;


int main()
{
        Map m((char*)"parameters.txt");
        PathPlanner p(m);
        WaypointsManager wm(p.getGoalNode(),m.gridFromPix(m.getStartLocationX()),m.gridFromPix(m.getStartLocationY()));
	Robot* robot = new Robot("localhost", 6665);
        MoveForward* mf = new MoveForward(robot);
        Turn* tu=new Turn(robot);
        float dy=m.pixFromGrid(wm.getPrevWaypoint().y)-m.pixFromGrid(wm.getWaypoint().y);
        float dx=m.pixFromGrid(wm.getPrevWaypoint().x)-m.pixFromGrid(wm.getWaypoint().x);
        float deg=(atan (dy/dx) * 180 / PI) - 20;
        tu->setAngle(deg * PI / 180);
        std::cout << robot->getYaw() << std::endl;
        sleep(10);
        tu->action();
        sleep(10);
        std::cout << robot->getYaw() << std::endl;
        sleep(10);
        mf->action();
        sleep(10);
        tu->action();
        sleep(5);
        mf->action();
        sleep(5);
        tu->action();
        sleep(5);
	return 0;
}




