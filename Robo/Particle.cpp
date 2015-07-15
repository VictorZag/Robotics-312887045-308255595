/* 
 * File:   Particle.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */


#include "Particle.h"

Particle::Particle(long x, long y, long yaw, double belief) {
    this->_x = x;
    this->_y = y;
    this->_yaw = yaw;
    this->_belief = belief;
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
    
    _belief = 1.5 * predBelief * ProbByMeasurement(laserArr);
}

long Particle::ProbByMeasurement(float* laserArr)
{
    return 1;
}

long Particle::ProbByMove(long deltaX, long deltaY, long deltaYaw)
{
    // As delta yaw is smaller so return Prob that close to 1
    // else return Prob that close to 0
    
    
    
    return 1;
}

double Particle::GetBelief() const
{
    return _belief;
}


long Particle::GetX() const{
    return _x;
}
long Particle::GetY() const{
    return _y;
}
long Particle::GetYaw() const{
    return _yaw;
}
double Particle::Getbelief() const{
    return _belief;
}
