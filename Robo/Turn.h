/* 
 * File:   Turn.h
 * Author: colman
 *
 * Created on July 7, 2015, 10:32 AM
 */

#ifndef TURN_H
#define	TURN_H

#include "Behavior.h"

class Turn : Behavior {
public:
    Turn(Robot *robot);
    virtual ~Turn();
    
    virtual bool startCond();
    virtual bool stopCond();
    virtual void action();
private:

};

#endif	/* TURN_H */

