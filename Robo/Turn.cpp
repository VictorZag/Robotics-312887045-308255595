/* 
 * File:   Turn.cpp
 * Author: colman
 * 
 * Created on July 7, 2015, 10:32 AM
 */

#include "Turn.h"
#define ANGLE 1

Turn::Turn(Robot *robot) : Behavior(robot){
}

Turn::~Turn() {
}

bool Turn::startCond()
{
	return true;
}

bool Turn::stopCond()
{
	return true;
}

void Turn::action()
{
	_robot->setSpeed(0, ANGLE);
}
