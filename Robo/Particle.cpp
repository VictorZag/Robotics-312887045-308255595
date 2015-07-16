/* 
 * File:   Particle.cpp
 * Author: colman
 * 
 * Created on June 26, 2015, 2:52 AM
 */


#include "Particle.h"

Particle::Particle(float x, float y, float yaw, float belief, Map *map, Robot *robot) {
    this->_x = x;
    this->_y = y;
    this->_yaw = yaw;
    this->_belief = belief;
    this->_currMap = map;
    this->_robot = robot;
    
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw)
{
    _x += deltaX;
    _y += deltaY;
    _yaw += deltaYaw;
    
    float predBelief = _belief * ProbByMove(deltaX, deltaY, deltaYaw);
    
    _belief = 1.5 * predBelief * ProbByMeasurement();
}

long Particle::ProbByMeasurement()
{
    float xObs, yObs;
    float robotYaw = _robot->getYaw();
    float robotX = _robot->getX();
    float robotY = _robot->getY();
    int minIndex = _robot->deg_to_index(MIN_ANGLE);
    int maxIndex = _robot->deg_to_index(MAX_ANGLE);

    float *scan = _robot->getLaserScan();

    for (int i = minIndex; i <= maxIndex; i++)
    {
            if (scan[i] < MAX_DIST_TO_OBSTACLE)
            {
              /*    xrob – x position of the robot
                    yrob – y position of the robot
                    α – robot’s orientation
                    β – angle of the sensor relative to the robot
                    d – distance between the robot and the obstacle
                    xobs – x position of the obstacle
                    yobs – y position of the obstacle*/
                
                //xobs = xrob + d · cos(α + β)
                xObs = robotX + scan[i] * cos(robotYaw + (i * 0.36 - 120));
                //yobs = yrob + d · sin(α + β)        
                yObs = robotY + scan[i] * sin(robotYaw + (i * 0.36 - 120));
                
                // we have two points, now according to map extimate if we have obstacle
                // if so give high prob 
                // else give low prob
                
                
            }
    }
    return 1;
}

float Particle::ProbByMove(float deltaX, float deltaY, float deltaYaw)
{
    // As delta yaw is smaller so return Prob that close to 1
    // else return Prob that close to 0
    float prob = (PI - deltaYaw)/(3*PI);
    
    if (deltaX <= 145/RWX)
    {
        prob+= (145/RWX - deltaX)/(145/RWX * 3);
    }
    
    if (deltaY <= 125/RWY)
    {
        prob+= (125/RWY - deltaY)/(125/RWY * 3);
    }
    
    return prob;
}

float Particle::GetBelief() const
{
    return _belief;
}

float Particle::GetX() const{
    return _x;
}
float Particle::GetY() const{
    return _y;
}
float Particle::GetYaw() const{
    return _yaw;
}
float Particle::Getbelief() const{
    return _belief;
}
