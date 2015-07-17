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

//double LocalizationManager::SumParticleBelief() {
//	return sum + p->getWeight();
//}

bool cmp(Particle a, Particle b){
return a.GetBelief() < b.GetBelief();}

//void LocalizationManager::Resample() {
//    //double w = std::accumulate(_particles.begin(), _particles.end(), double(0), sum_particle_weight<State>);
//    //std::for_each(particles.begin(), particles.end(), divide_weight<State>(w) );
//    
//    // sort, with highest belief first
//    std::sort(_particles.begin(), _particles.end(), cmp);
//    // now we append
//    int N = _particles.size();
//    int newN = 0;
//    for (int i = 0; i < N; ++i) {
//            int copies = round(_particles[i]->Getbelief() * N);
//            for (int j = 0; j < copies; ++j) {
//                    Particle *newp = new Particle(_particles[i]->GetX(),
//                                                  _particles[i]->GetY(),
//                                                  _particles[i]->GetYaw(),
//                                                  _particles[i]->Getbelief());
//                    _particles.push_back(newp);
//                    newN++;
//                    if (newN == N) {
//                            // now remove old items
//                            _particles.erase(_particles.begin(), _particles.begin()+N);
//                            assert ( set.particles.size() == newN);
//                            return;
//                    }
//            }
//    }
//    while (newN < N) {
//        // duplicate particle with highest weight to get exactly same number again
//        Particle *newp = new Particle(_particles[0]->GetX(),
//                                      _particles[0]->GetY(),
//                                      _particles[0]->GetYaw(),
//                                      _particles[0]->Getbelief());
//        _particles.push_back(newp);
//        newN++; 
//    }
//    _particles.erase(_particles.begin(), _particles.begin()+N);
//}

void LocalizationManager::Update(float deltaX, float deltaY, float deltaYaw, float* laserArr)
{
    std::vector<Particle*>::iterator iter = _particles.begin();
    while (iter != _particles.end())
    {
        (*iter)->Update(deltaX, deltaY, deltaYaw);
        if ((*iter)->GetBelief() < 0.5)
        {
            iter = _particles.erase(iter);
        }
        else if ((*iter)->GetBelief() > 0.8)
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

float LocalizationManager::getRandom(float curr,float range)
{
    return ((range)*((float)rand()/RAND_MAX))*pow(-1,(int)rand())+curr;
}


