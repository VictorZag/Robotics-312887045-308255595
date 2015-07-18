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
#include "WaypointsManager.h"
#include <math.h>       /* cos, sin */
#include <algorithm>    // std::swap


class Particle {
public:
    Particle(float x, float y, float yaw, float belief, Map *map, Robot *robot, WaypointsManager *wayPoint);
    Particle(const Particle& orig);
    virtual ~Particle();
    
    void Update(float deltaX, float deltaY, float deltaYaw);
    
    float ProbByMeasurement();
    
    float GetBelief() const;
    float GetX() const;
    float GetY() const;
    float GetYaw() const;
    float Getbelief() const;
    Map* GetMap() const;
    Robot* GetRobot() const;
    WaypointsManager* GetWayPoint() const;


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
    WaypointsManager *_wayPoint;
    float ProbByMove(float deltaX, float deltaY, float deltaYaw);
    LocationF Line( float x1,  float y1,  float x2,  float y2);

};

#endif	/* PARTICLE_H */

