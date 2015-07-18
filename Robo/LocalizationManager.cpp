/* 
 * File:   LocalizationManager.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */


#include "LocalizationManager.h"


LocalizationManager::LocalizationManager(Map *map, Robot *robot, WaypointsManager *wayPoint) {
    
    float xRobot = robot->getX();
    float yRobot = robot->getY();
    float yawRobot = robot->getYaw();
    
    for (int i=0; i<PART_COUNT; i++)
    {
        float xParticle = getRandom(xRobot,RANGE_RANDOM);
        float yParticle = getRandom(yRobot,RANGE_RANDOM);
        float yawParticle = getRandom(yawRobot,PI);
        Particle *newp = new Particle(xParticle,
                                    yParticle,
                                    yawParticle,
                                    1,
                                    map,
                                    robot,
                                    wayPoint);
        _particles.push_back(newp);
    }
}

LocalizationManager::LocalizationManager(const LocalizationManager& orig) {
}

LocalizationManager::~LocalizationManager() {
}
bool cmp(Particle* a, Particle* b){
return a->GetBelief() > b->GetBelief();}

void LocalizationManager::Update(float deltaX, float deltaY, float deltaYaw, float* laserArr)
{
    // sort, with low belief first
    std::sort(_particles.begin(), _particles.end(), cmp);
    
    std::vector<Particle*>::iterator iter = _particles.begin();
    while (iter != _particles.end())
    {
        Particle* currPart = (*iter);
        currPart->Update(deltaX, deltaY, deltaYaw);
        if ((*iter)->GetBelief() <= 0.5)
        {
            iter = _particles.erase(iter);
        }
        else if ((*iter)->GetBelief() >= 0.8)
        {
            // Create random childs particles
            for(int i=0; (i<10 && _particles.size() < PART_COUNT);i++)
            {
                float xParticle = getRandom(currPart->GetX(), RANGE_RANDOM);
                float yParticle = getRandom(currPart->GetY(), RANGE_RANDOM);
                float yawParticle = getRandom(currPart->GetYaw(), PI);
                Particle *newp = new Particle(xParticle,
                                                yParticle,
                                                yawParticle,
                                                currPart->GetBelief(),
                                                currPart->GetMap(),
                                                currPart->GetRobot(),
                                                currPart->GetWayPoint());
                
                _particles.push_back(newp);
            }
            
            ++iter;
        }
        else
        {
           ++iter;
        }
    }
}

float LocalizationManager::getRandom(float curr,float range)
{
    return ((range)*((float)rand()/RAND_MAX))*pow(-1,(int)rand())+curr;
}


