/* 
 * File:   Particle.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:52 AM
 */


#ifndef PARTICLE_H
#define	PARTICLE_H

#include "Globals.h" 
#include "Map.h"
#include "Robot.h"
#include <math.h>       /* cos, sin */

class Particle {
public:
    Particle(float x, float y, float yaw, float belief, Map *map, Robot *robot);
    Particle(const Particle& orig);
    virtual ~Particle();
    
    void Update(float deltaX, float deltaY, float deltaYaw);
    
    float ProbByMeasurement();
    
    double GetBelief() const;
    float GetX() const;
    float GetY() const;
    float GetYaw() const;
    float Getbelief() const;

    bool operator<(const Particle& obj) const {
    return this->GetBelief() < obj.GetBelief();
    }
    
    Particle *clone();
    
private:
    
    float _x;
    float _y;
    float _yaw;
    float _belief;
    Map *_currMap;
    Robot *_robot;
    long ProbByMove(float deltaX, float deltaY, float deltaYaw);

};

#endif	/* PARTICLE_H */

