/* 
 * File:   Particle.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */

#include "Particle.h"

Particle::Particle() {
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

void Particle::Update(long deltaX, long deltaY, long deltaYaw, float* laserArr)
{
    _x += deltaX;
    _y += deltaY;
    _yaw += deltaYaw;
    
    long predBelief = _belief * ProbByMove(deltaX, deltaY, deltaYaw);
    
    _belief = 1.5 * predBelief * ProbByMeasurement();
}

long Particle::ProbByMeasurement()
{
    return 1;
}

long Particle::ProbByMove(long deltaX, long deltaY, long deltaYaw)
{
    // As delta yaw is smaller so return Prob that close to 1
    // else return Prob that close to 0
    
    
    
    return 1;
}

long Particle::GetBelief()
{
    return _belief;
}
