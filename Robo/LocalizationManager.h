/* 
 * File:   LocalizationManager.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:52 AM
 */

#ifndef LOCALIZATIONMANAGER_H
#define	LOCALIZATIONMANAGER_H

#define PART_COUNT 200

#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <cassert>
#include <cmath>


#include "Particle.h"

using namespace std;

class LocalizationManager {
public:
    LocalizationManager(Map *map, Robot *robot, WaypointsManager *wayPoint);
    LocalizationManager(const LocalizationManager& orig);
    virtual ~LocalizationManager();
    
       
//    void Resample(float deltaX, float deltaY, float deltaYaw, float* laserArr);
    void Update(float deltaX, float deltaY, float deltaYaw, float* laserArr);
    
    float getRandom(float curr,float range);
    
private:
    vector<Particle*> _particles;
    

};



#endif	/* LOCALIZATIONMANAGER_H */

