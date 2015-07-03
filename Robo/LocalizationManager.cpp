/* 
 * File:   LocalizationManager.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */

#include "LocalizationManager.h"
#include "Particle.h"

LocalizationManager::LocalizationManager() {
}

LocalizationManager::LocalizationManager(const LocalizationManager& orig) {
}

LocalizationManager::~LocalizationManager() {
}

void LocalizationManager::Update(long deltaX, long deltaY, long deltaYaw, float* laserArr)
{
    std::vector<Particle>::iterator iter = _particles.begin();
    while (iter != _particles.end())
    {
        (*iter).Update(deltaX, deltaY, deltaYaw, laserArr);
        if ((*iter).GetBelief() < 0.5)
        {
            iter = _particles.erase(iter);
        }
        else if ((*iter).GetBelief() > 0.8)
        {
           // Create random childs particles 
            ++iter;
        }
        else
        {
           ++iter;
        }
    }
}

