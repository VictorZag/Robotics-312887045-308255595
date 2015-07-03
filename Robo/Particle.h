/* 
 * File:   Particle.h
 * Author: colman
 *
 * Created on June 26, 2015, 2:52 AM
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

class Particle {
public:
    Particle();
    Particle(const Particle& orig);
    virtual ~Particle();
    
    void Update(long deltaX, long deltaY, long deltaYaw, float* laserArr);
    
    long ProbByMeasurement();
    
    long GetBelief();
    
private:
    
    long _x;
    long _y;
    long _yaw;
    
    long _belief;
    
    long ProbByMove(long deltaX, long deltaY, long deltaYaw);

};

#endif	/* PARTICLE_H */

