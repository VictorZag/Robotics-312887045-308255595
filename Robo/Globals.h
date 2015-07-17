/* 
 * File:   Globals.h
 * Author: colman
 *
 * Created on July 15, 2015, 9:49 AM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#define PI 3.14159265
#define RWX 38.2
#define RWY 39
#define MIN_ANGLE -30
#define MAX_ANGLE 30
#define MAX_DIST_TO_OBSTACLE 0.5
#define FORWARD_SPEED 0.1
#define LASER_RANGE 100
#define MAX_LASER_DIST 20
#define RANGE_RANDOM 2

class LocationF
{
public:
    float x;
    float y;
};

#endif	/* GLOBALS_H */

