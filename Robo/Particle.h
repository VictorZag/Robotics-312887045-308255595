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
    Particle(long x, long y, long yaw, double _belief);
    Particle(const Particle& orig);
    virtual ~Particle();
    
    void Update(long deltaX, long deltaY, long deltaYaw, float* laserArr);
    
    long ProbByMeasurement(float* laserArr);
    
    double GetBelief() const;
    long GetX() const;
    long GetY() const;
    long GetYaw() const;
    double Getbelief() const;

    bool operator<(const Particle& obj) const {
    return this->GetBelief() < obj.GetBelief();
    }
    
    Particle *clone();
    
private:
    
    long _x;
    long _y;
    long _yaw;
    double _belief;
    
    long ProbByMove(long deltaX, long deltaY, long deltaYaw);

};

#endif	/* PARTICLE_H */

