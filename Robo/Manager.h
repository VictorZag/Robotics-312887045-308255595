/* 
 * File:   Manager.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:58 AM
 */

#ifndef MANAGER_H
#define	MANAGER_H


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
#include "Particle.h"
#include "LocalizationManager.h"
#include "Globals.h"

using namespace PlayerCc;
using namespace std;

class Manager {
public:
    Manager();
    Manager(const Manager& orig);
    virtual ~Manager();
private:

};

#endif	/* MANAGER_H */

