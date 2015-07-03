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
        if ((*iter).GetBelief() < 1)
        {
            iter = _particles.erase(iter);
        }
        else if ((*iter).GetBelief() > 2)
        {
           // Create childes randoms child particles 
            ++iter;
        }
        else
        {
           ++iter;
        }
    }
    for(std::vector<Particle>::size_type i = 0; i != _particles.size(); i++) {
        _particles[i].Update(deltaX, deltaY, deltaYaw, laserArr);
        
        if (_particles[i].GetBelief() < 1)
        {
            
        }
        
    }
}

