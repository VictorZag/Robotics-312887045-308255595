/* 
 * File:   LocalizationManager.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:52 AM
 */

#ifndef LOCALIZATIONMANAGER_H
#define	LOCALIZATIONMANAGER_H

#define PART_COUNT 200

#include <vector>
#include <queue>

#include "Particle.h"

using namespace std;

class LocalizationManager {
public:
    LocalizationManager();
    LocalizationManager(const LocalizationManager& orig);
    virtual ~LocalizationManager();
    
    void Update(long deltaX, long deltaY, long deltaYaw, float* laserArr);
private:
    
    /*Particle _particles[PART_COUNT];*/
    vector<Particle> _particles;
    

};

#endif	/* LOCALIZATIONMANAGER_H */

